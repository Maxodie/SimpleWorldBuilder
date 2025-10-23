#pragma once

#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/AssetManager/Importer/ModelImporter.hpp"
#include "Core/Serializer/SceneSerializer.hpp"
#include "Core/Commons/Scene.hpp"
#include "Core/Utils/FileSystem.hpp"

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
    WB_FORCEINLINE bool IsMetaDataAssetValid(AssetID id) const
    {
        return m_metaDataRegistry.find(id) != m_metaDataRegistry.end() && id != EMPTY_ASSET;
    }

    virtual WeakPtr<Asset> GetAsset(AssetID id) override;

    WeakPtr<Asset> LoadAsset(const AssetMetaData& metaData);

    template<typename TAsset>
    WeakPtr<TAsset> CreateAsset(AssetType type, const Path& path, const std::string& name)
    {
        SharedPtr<TAsset> asset = MakeShared<TAsset>();
        AssetID nextID = s_maxAssetID + 1;

        asset->id = nextID;
        asset->type = type;

        switch(type)
        {
            case AssetType::MODEL:
            {
                break;
            }
            case AssetType::SHADER:
            {
                break;
            }
            case AssetType::SCENE:
            {
                std::string fullName = name + s_sceneExtension;
                SceneSerializer::Serialize(*asset, path / fullName);
                break;
            }
            case AssetType::TEXTURE:
                break;
            case AssetType::MATERIAL:
                break;

            case AssetType::FOLDER:
                break;
            case AssetType::UNKNOWN:
                break;
            default:
                break;
        }

        if(asset)
        {
            ++s_maxAssetID;
            m_registry[asset->id] = asset;
            return asset;
        }

        CORE_LOG_ERROR("could not create asset of type %d", type);
        return {};
    }

    WeakPtr<AssetMetaData> GetMetaData(AssetID id);
    WeakPtr<AssetMetaData> CreateMetaData(const Path& path);
    void DeleteMeta(WeakPtr<AssetMetaData> meta);
    WeakPtr<AssetMetaData> LoadMetaData(const Path& path);
    void LoadAllProjectMetaData();
    void SaveAllProjectMetaData();

    virtual bool CheckPackagesValidity() override;

    WB_INLINE MetaDataRegistry& GetMetaDataRegistry() { return m_metaDataRegistry; }

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

    WB_INLINE const static std::string s_sceneExtension = ".scene";
};

}
