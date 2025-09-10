#include "Core/Serializer/AssetManagerSerializer.hpp"
#include "Core/Project.hpp"
#include "Core/Serializer/Serializer.hpp"
#include "Core/Utils/FileSystem.hpp"
#include "yaml-cpp/yaml.h"

namespace WB
{

bool AssetManagerSerializer::Serialize(const struct AssetMetaData& metaData, const Path& path)
{
    YAML::Emitter emitter;

    std::string stringPath{metaData.path.string()};

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "path" << YAML::Value << stringPath;
    emitter << YAML::Key << "type" << YAML::Value << Serializer::AssetTypeAsString(metaData.type);
    emitter << YAML::Key << "id" << YAML::Value << metaData.id;
    emitter << YAML::Key << "name" << YAML::Value << metaData.name;
    emitter << YAML::EndSeq;

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool AssetManagerSerializer::Deserialize(AssetMetaData& metaData, const Path& path)
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

        metaData.path = root["path"].as<std::string>();
        metaData.type = Serializer::AssetStringAsType(root["type"].as<std::string>());
        metaData.id = root["id"].as<AssetID>();
        metaData.name = root["name"].as<std::string>();

        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}

bool AssetManagerSerializer::Serialize(const MetaDataRegistry& metaDataRegistry, const Path& path)
{
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
        emitter << YAML::Key << "METADATA";
        emitter << YAML::Value << YAML::BeginSeq;

            for(auto& [key, metaData] : metaDataRegistry)
            {
                Path path = metaData->path;
                EditorAssetManager::ConvertToMetaPath(path);
                std::string pathString{path.string()};

                emitter << pathString;
            }

        emitter << YAML::EndSeq;
    emitter << YAML::EndMap;

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool AssetManagerSerializer::Deserialize(MetaDataRegistry& metaDataRegistry, const Path& path)
{
    if(!FileSystem::Exists(path))
    {
        return false;
    }
    try
    {
        auto root = YAML::LoadFile(path.string());

        if(root.IsNull())
        {
            CORE_LOG_ERROR("failed to parse %s", path.string().c_str());
            return false;
        }

        for(const auto& node : root["METADATA"])
        {
            std::string metaFile = node.as<std::string>();
            if(!FileSystem::Exists(metaFile))
            {
                continue;
            }

            Project::GetActive()->GetEditorAssetManager()->LoadMetaData(metaFile);
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
