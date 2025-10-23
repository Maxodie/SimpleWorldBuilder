#include "Core/Core.hpp"
#include "Core/Serializer/ScenePackageSerializer.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"
#include "yaml-cpp/yaml.h"

namespace WB
{

bool ScenePackageSerializer::Serialize(const ScenePackageRegistry& packageRegistry, const Path& path)
{

    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
        for(const auto& package : packageRegistry)
        {
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Scene" << YAML::Value << package->GetScene();
        for(AssetID i = 0; i < package->GetAssets().size(); i++)
            {
                emitter << YAML::Key << "AssetID" + std::to_string(i);
                emitter <<YAML::Value << package->GetAssets()[i];
            }
            emitter << YAML::EndMap;
        }
    emitter << YAML::EndSeq;

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool ScenePackageSerializer::Deserialize(ScenePackageRegistry& packageRegistry, const Path& path)
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

        CORE_LOG_DEBUG("Start loading scene package at path %s", path.string().c_str());

        for (const auto& packageMap : root)
        {
            SharedPtr<ScenePackage> package = MakeShared<ScenePackage>();

            package->SetScene(packageMap["Scene"].as<AssetID>());
            for(int i = 0; i < packageMap.size() - 1; i++)
            {
                package->AddUniqueAsset(packageMap["AssetID" + std::to_string(i)].as<AssetID>());
            }

            packageRegistry.push_back(package);
            CORE_LOG_DEBUG("Package found with scene id %zu", package->GetScene());
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
