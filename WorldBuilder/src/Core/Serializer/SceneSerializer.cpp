#include "Core/Serializer/SceneSerializer.hpp"
#include "Core/Commons/Scene.hpp"
#include "Core/ECS/Entity.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "Core/Project.hpp"
#include "Core/Renderer/Model.hpp"
#include "Core/Serializer/Serializer.hpp"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/yaml.h"

namespace WB
{

bool SceneSerializer::Serialize(const Scene3D& scene, const Path& path)
{
    YAML::Emitter emitter;

    emitter << YAML::BeginSeq;

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
                if(scene.Get<ModelComponent>(entityHandle).asset.lock())
                {
                    emitter << YAML::Value << scene.Get<ModelComponent>(entityHandle).asset.lock()->id;
                }
                else
                {
                    emitter << YAML::Value << EMPTY_ASSET;
                }
            }

            emitter << YAML::EndMap;
        }
    );

    emitter << YAML::EndSeq;
    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool SceneSerializer::Deserialize(Scene3D& scene, const Path& path)
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

        for(const auto& entityNode : root)
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
                model.asset = Project::GetActive()->GetAssetManager()->GetAsset<ModelAsset>(modelID);
                entity.AddComponent<ModelComponent>(model);
            }
        }

        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}


}
