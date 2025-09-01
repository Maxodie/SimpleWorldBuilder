#pragma once

#include "Core/AssetManager/AssetManagerBase.hpp"

namespace WB
{

struct AssetMetaData
{
    Path path = "";
    AssetType type = AssetType::UNKNOWN;
    AssetID id = EMPTY_ASSET;
};

class EditorAssetManager : public AssetManagerBase
{
public:
    WB_INLINE bool IsMetaDataAssetValid(AssetID id)
    {
        return m_metaDataRegistry.find(id) != m_metaDataRegistry.end();
    }

    virtual WeakPtr<Asset> GetAsset(AssetID id) override;
    WeakPtr<Asset> CreateAsset(const AssetMetaData& metaData);

    WeakPtr<AssetMetaData> GetMetaData(AssetID id);
    WeakPtr<AssetMetaData> CreateMetaData(const Path& path);
    WeakPtr<AssetMetaData> LoadMetaData(const Path& path);

public:
    WB_INLINE static const std::string s_metaExtention = ".meta";

private:
    std::unordered_map<AssetID, SharedPtr<AssetMetaData>> m_metaDataRegistry;
    static AssetID assetID;
};

}
