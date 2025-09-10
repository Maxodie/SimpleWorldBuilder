#pragma once

#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/AssetManager/Importer/ModelImporter.hpp"

namespace WB
{


struct AssetMetaData
{
    Path path = "";
    AssetType type = AssetType::UNKNOWN;
    AssetID id = EMPTY_ASSET;
    std::string name = "Empty";
};

using MetaDataRegistry = std::unordered_map<AssetID, SharedPtr<AssetMetaData>>;

class EditorAssetManager : public AssetManagerBase
{
public:
    WB_INLINE bool IsMetaDataAssetValid(AssetID id) const
    {
        return m_metaDataRegistry.find(id) != m_metaDataRegistry.end() && id != EMPTY_ASSET;
    }

    virtual WeakPtr<Asset> GetAsset(AssetID id) override;
    virtual void UnloadAsset(AssetID id) override;

    WeakPtr<Asset> CreateAsset(const AssetMetaData& metaData);

    WeakPtr<AssetMetaData> GetMetaData(AssetID id);
    WeakPtr<AssetMetaData> CreateMetaData(const Path& path);
    WeakPtr<AssetMetaData> LoadMetaData(const Path& path);
    void LoadAllProjectMetaData();
    void SaveAllProjectMetaData();

    WB_INLINE MetaDataRegistry& GetMetaDataRegistry() { return m_metaDataRegistry; }

public:
    WB_INLINE static const std::string s_metaExtention = ".meta";
    WB_INLINE static void ConvertToMetaPath(Path& path)
    {
        FileSystem::ReplaceExtension(path, s_metaExtention);
    }

    WB_INLINE static Path ConvertToMetaPath(const Path& path)
    {
        Path metaPath = path;
        FileSystem::ReplaceExtension(metaPath, s_metaExtention);
        return metaPath;
    }

private:
    MetaDataRegistry m_metaDataRegistry;
};

}
