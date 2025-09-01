#pragma once

#include "Core/AssetManager/Asset.hpp"

namespace WB
{

class AssetManagerBase
{
public:
    AssetManagerBase() = default;
    virtual ~AssetManagerBase() = default;

    WB_INLINE virtual bool IsAssetValid(AssetID id)
    {
        return m_registry.find(id) != m_registry.end();
    }

    virtual WeakPtr<Asset> GetAsset(AssetID id);

protected:
    std::unordered_map<AssetID, SharedPtr<Asset>> m_registry;
};

}
