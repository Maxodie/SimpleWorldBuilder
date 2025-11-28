#include "Core/Serializer/SceneSerializer.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/Commons/Scene.hpp"
#include "Core/ECS/Entity.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"
#include "Core/Renderer/Model.hpp"
#include "Core/Serializer/ScenePackageSerializer.hpp"
#include "Core/Serializer/Serializer.hpp"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/yaml.h"

namespace WB
{

bool SceneSerializer::Serialize(const Scene3D& scene, const Path& path)
{
    SharedPtr<ScenePackage> scenePackage = MakeShared<ScenePackage>();
    scenePackage->SetScene(scene.id);

    YAML::Emitter emitter;

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "id" << YAML::Value << scene.id;
    emitter << YAML::Key << "entities" << YAML::Value << YAML::BeginSeq;

    scene.Each(
        [&](auto entityHandle)
        {
            emitter << YAML::BeginMap;

            if(scene.Has<InfoComponent>(entityHandle))
            {
                emitter << YAML::Key << "info";
                emitter << YAML::Value << Serializer::EncodeInfo(scene.Get<InfoComponent>(entityHandle));
            }

            if(scene.Has<TransformComponent>(entityHandle))
            {
                emitter << YAML::Key << "transform";
                emitter << YAML::Value << Serializer::EncodeTransform(scene.Get<TransformComponent>(entityHandle));
            }

            if(scene.Has<ModelComponent>(entityHandle))
            {
                emitter << YAML::Key << "model";
                AssetID id = EMPTY_ASSET;
                AssetID matID = EMPTY_ASSET;
                const ModelComponent& modelComp = scene.Get<ModelComponent>(entityHandle);
                if(modelComp.asset.lock())
                {
                    id = modelComp.asset.lock()->id;
                }
                if(modelComp.material.lock())
                {
                    matID = modelComp.material.lock()->id;
                }

                emitter << YAML::Value << id;
                emitter << YAML::Key << "material";
                emitter << YAML::Value << matID;
                scenePackage->AddUniqueAsset(id);
            }

            emitter << YAML::EndMap;
        }
    );
    emitter << YAML::EndSeq;

    Project::GetActive()->GetAssetManager()->ReplaceOrAddPackage(scenePackage);

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool SceneSerializer::Deserialize(Scene3D& scene, const Path& path, bool loadLinkedAssets)
{
    if(!FileSystem::Exists(path))
    {
        return false;
    }

    try
    {
        YAML::Node root = YAML::LoadFile(path.string());
        if(root.IsNull())
        {
            CORE_LOG_ERROR("failed to parse %s", path.string().c_str());
            return false;
        }

        CORE_LOG_DEBUG("Start loading scene asset at path %s", path.string().c_str());

        SharedPtr<ScenePackage> scenePackage = MakeShared<ScenePackage>();

        scene.id = root["id"].as<AssetID>();
        scenePackage->SetScene(scene.id);

        for(const auto& entityNode : root["entities"])
        {
            InfoComponent infoComponent;
            if(const auto& infoNode = entityNode["info"])
            {
                Serializer::DecodeInfo(infoComponent, infoNode);
            }

            Entity entity = scene.CreateEntity(infoComponent.handle);
            entity.AddComponent<InfoComponent>(infoComponent);

            if(const auto& transformNode = entityNode["transform"])
            {
                TransformComponent tr;
                Serializer::DecodeTransform(tr, transformNode);
                entity.AddComponent<TransformComponent>(tr);
            }



            if(const auto& modelNode = entityNode["model"])
            {
                ModelComponent model;
                AssetID modelID = modelNode.as<AssetID>();
                AssetID materialID = EMPTY_ASSET;

                if(const auto& material = entityNode["material"])
                {
                    materialID = material.as<AssetID>();
                }

                if(loadLinkedAssets)
                {
                    if(modelID != EMPTY_ASSET)
                    {
                        model.asset = Project::GetActive()->GetAssetManager()->GetAsset<ModelAsset>(modelID);
                        CORE_LOG_DEBUG("scene serializer asset loaded, id %d", modelID);
                    }

                    if(materialID != EMPTY_ASSET)
                    {
                        model.material = Project::GetActive()->GetAssetManager()->GetAsset<Material>(materialID);
                        CORE_LOG_DEBUG("scene serializer asset loaded, id %d", materialID);
                    }
                }

                if(const auto& modelNode = entityNode["material"])
                {
                    if(loadLinkedAssets)
                    {
                        model.asset = Project::GetActive()->GetAssetManager()->GetAsset<ModelAsset>(modelID);
                    }
                }

                scenePackage->AddUniqueAsset(modelID);
                scenePackage->AddUniqueAsset(materialID);
                entity.AddComponent<ModelComponent>(model);
            }
        }

        Project::GetActive()->GetAssetManager()->ReplaceOrAddPackage(scenePackage);

        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}


}
