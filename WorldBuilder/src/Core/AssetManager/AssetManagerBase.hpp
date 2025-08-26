#pragma once

#include "Core/AssetManager/Asset.hpp"

namespace WB
{

class AssetManagerBase
{
public:
    AssetManagerBase() = default;
    virtual ~AssetManagerBase() = delete;

    WB_INLINE virtual bool IsAssetValid(AssetID id)
    {
        return m_registry.find(id) != m_registry.end();
    }

    virtual SharedPtr<Asset> GetAsset(AssetID id);

private:
    std::unordered_map<AssetID, SharedPtr<Asset>> m_registry;
};

}
