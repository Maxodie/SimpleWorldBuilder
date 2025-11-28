#include "Core/AssetManager/Engine/EngineAssetManager.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/Texture2D.hpp"
#include "yaml-cpp/yaml.h"

namespace WB
{

EngineAssetManager* EngineAssetManager::s_instance;

void EngineAssetManager::Init()
{
    LoadAssetList("DefaultRessources/assets/EngineEditorAssetList.config");
}

void EngineAssetManager::Shutdown()
{
    Destroy();
}

WeakPtr<Texture2D> EngineAssetManager::GetAsset(const std::string& key)
{
    if(IsAssetValid(key))
    {
        return m_registry[key];
    }
    else
    {
        CORE_LOG_ERROR("Faled to get asset asset %s", key.c_str());
    }

    return {};
}

void EngineAssetManager::LoadAssetList(const Path& path)
{
    //load yaml list as pair of string : texture
    if(!FileSystem::Exists(path))
    {
        CORE_LOG_ERROR("Failed to load asset list at %s", path.c_str());
        return;
    }

    try
    {
        YAML::Node root = YAML::LoadFile(path.string());
        if(root.IsNull())
        {
            CORE_LOG_ERROR("failed to parse %s", path.string().c_str());
            return;
        }

        CORE_LOG_DEBUG("Start loading engine asset at path %s", path.string().c_str());

        if(root["root"])
        {
            s_rootAssetPath = root["root"].as<std::string>();
        }

        if(root["assets"])
        {
            for(const auto& node : root["assets"])
            {
                if(node["path"] && node["key"])
                {
                    std::string texturePath = node["path"].as<std::string>();
                    std::string key = node["key"].as<std::string>();
                    if(!IsAssetValid(key))
                    {
                        const Path fullPath = s_rootAssetPath/texturePath;
                        SharedPtr<Texture2D> texture = Texture2D::CreateTexture(fullPath);
                        m_registry[key] = texture;
                    }
                    else
                    {
                        CORE_LOG_ERROR("Trying to load an asset that already exists key %s path %s", key.c_str(), path.c_str());
                    }
                }
            }
        }

        return;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return;
    }
}

void EngineAssetManager::FreeAssetList()
{
    m_registry.clear();
}

}
