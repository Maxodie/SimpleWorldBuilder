#pragma once

#include "Core/AssetManager/AssetManagerBase.hpp"

namespace WB
{

struct AssetMetaData
{
    Path path;
};

class EditorAssetManager : public AssetManagerBase
{
public:
    WB_INLINE bool IsMetaDataAssetValid(AssetID id)
    {
        return m_metaDataRegistry.find(id) != m_metaDataRegistry.end();
    }

    virtual SharedPtr<Asset> GetAsset(AssetID id) override;

public:
    WB_INLINE static const std::string metaExtention = ".meta";

private:
    std::unordered_map<AssetID, AssetMetaData> m_metaDataRegistry;
};

}
