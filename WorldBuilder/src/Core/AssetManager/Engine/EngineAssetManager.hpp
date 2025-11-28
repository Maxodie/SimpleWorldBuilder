#pragma once

#include "Core/Utils/FileSystem.hpp"
#include <unordered_map>
namespace WB
{


class EngineAssetManager
{
    using AssetRegistry = std::unordered_map<std::string, SharedPtr<class Texture2D>>;

public:
    void Init();
    void Shutdown();

    WeakPtr<class Texture2D> GetAsset(const std::string& key);

    WB_FORCEINLINE bool IsAssetValid(const std::string& key) const
    {
        return m_registry.find(key) != m_registry.end();
    }

    static constexpr WB_INLINE EngineAssetManager& Get()
    {
        if(!s_instance)
        {
            Create();
        }

        return *s_instance;
    }

private:
    static WB_INLINE EngineAssetManager& Create()
    {
        s_instance = new EngineAssetManager();
        CORE_LOG_SUCCESS("Engine Asset Manager created");
        return *s_instance;
    }

    static WB_INLINE void Destroy()
    {
        delete s_instance;
        CORE_LOG_SUCCESS("Engine Asset Manager destroyed");
    }

    void LoadAssetList(const Path& path);
    void FreeAssetList();

private:
    static EngineAssetManager* s_instance;
    AssetRegistry m_registry;

    WB_INLINE static Path s_rootAssetPath;
};

}
