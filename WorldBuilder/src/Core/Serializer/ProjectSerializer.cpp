#include "Core/Serializer/ProjectSerializer.hpp"
#include "Core/Utils/FileSystem.hpp"
#include "Core/Project.hpp"
#include "Core/AssetManager/EditorAssetManager.hpp"
#include "Core/Serializer/Serializer.hpp"

#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/convert.h"

namespace WB
{

bool ProjectSerializer::Serialize(const ProjectSettings& settings, const Path& path)
{
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "project_name" << YAML::Value << settings.projectName;
    emitter << YAML::Key << "project_path" << YAML::Value << settings.projectPath.string();
    emitter << YAML::Key << "project_assets_path" << YAML::Value << settings.projectAssetPath.string();
    emitter << YAML::EndMap;

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool ProjectSerializer::Deserialize(ProjectSettings& settings, const Path& path)
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

        settings.projectName = root["project_name"].as<std::string>();
        settings.projectPath = root["project_path"].as<std::string>();
        settings.projectAssetPath = root["project_assets_path"].as<std::string>();
        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}

bool ProjectSerializer::Serialize(const struct ProjectList& list, const Path& path)
{
    YAML::Emitter emitter;

    YAML::convert<std::vector<std::string>> convertedStrings;
    std::vector<std::string> stringPaths{list.paths.size()};
    for(int i = 0; i < list.paths.size(); i++)
    {
        stringPaths[i] = list.paths[i].string();
    }

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "paths" << YAML::Value << convertedStrings.encode(stringPaths);
    emitter << YAML::Key << "names" << YAML::Value << convertedStrings.encode(list.names);
    emitter << YAML::EndSeq;
    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool ProjectSerializer::Deserialize(ProjectList& list, const Path& path)
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

        std::vector<std::string> stringPaths = root["paths"].as<std::vector<std::string>>();

        list.paths = std::vector<Path>{stringPaths.size()};
        for(int i = 0; i < list.paths.size(); i++)
        {
            list.paths[i] = stringPaths[i];
        }
        list.names = root["names"].as<std::vector<std::string>>();

        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}

bool ProjectSerializer::Serialize(const struct AssetMetaData& metaData, const Path& path)
{
    YAML::Emitter emitter;

    std::string stringPath{metaData.path.string()};

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "path" << YAML::Value << stringPath;
    emitter << YAML::Key << "type" << YAML::Value << Serializer::AssetTypeAsString(metaData.type);
    emitter << YAML::Key << "id" << YAML::Value << metaData.id;
    emitter << YAML::EndSeq;

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool ProjectSerializer::Deserialize(AssetMetaData& metaData, const Path& path)
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

        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}

}
