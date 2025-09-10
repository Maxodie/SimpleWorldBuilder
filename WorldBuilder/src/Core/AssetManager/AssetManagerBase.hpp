#pragma once

#include "Core/AssetManager/Asset.hpp"
#include "Core/Core.hpp"

namespace WB
{

class AssetManagerBase
{
public:
    AssetManagerBase() = default;
    virtual ~AssetManagerBase() = default;

    WB_INLINE virtual bool IsAssetValid(AssetID id) const
    {
        return m_registry.find(id) != m_registry.end() && id != EMPTY_ASSET;
    }

    template<typename TAsset>
    WB_INLINE WeakPtr<TAsset> GetAsset(AssetID id)
    {
        if(GetAsset(id).lock())
        {
            return static_pointer_cast<TAsset>(GetAsset(id).lock());
        }
        CORE_LOG_ERROR("asset does not exist");
        return {};
    }

    virtual WeakPtr<Asset> GetAsset(AssetID id) = 0;
    virtual void UnloadAsset(AssetID id) = 0;

protected:
    std::unordered_map<AssetID, SharedPtr<Asset>> m_registry;
    WB_INLINE static AssetID s_maxAssetID = EMPTY_ASSET;
};

}
