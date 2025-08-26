#pragma once

#include "Core/AssetManager/AssetManagerBase.hpp"

namespace WB
{

struct AssetMetaData
{
    Path path;
    std::string name;
};

class EditorAssetManager : public AssetManagerBase
{
public:
    WB_INLINE bool IsMetaDataAssetValid(AssetID id)
    {
        return m_metaDataRegistry.find(id) != m_metaDataRegistry.end();
    }

    virtual SharedPtr<Asset> GetAsset(AssetID id) override;

private:
    std::unordered_map<AssetID, AssetMetaData> m_metaDataRegistry;
};

}
