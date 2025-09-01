#include "Core/AssetManager/EditorAssetManager.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/AssetManager/Importer/ModelImporter.hpp"
#include "Core/Project.hpp"
#include "Core/Core.hpp"
#include "Core/Utils/FileSystem.hpp"

namespace WB
{

AssetID EditorAssetManager::assetID = EMPTY_ASSET;

WeakPtr<Asset> EditorAssetManager::GetAsset(AssetID id)
{
    if(IsAssetValid(id))
    {
        return m_registry[id];
    }
    else
    {
        WeakPtr<AssetMetaData> metaData = GetMetaData(id);
        if(metaData.lock())
        {
            return CreateAsset(*metaData.lock());
        }
    }

    CORE_LOG_ERROR("could not find asset id %d", id);
    return {};
}

WeakPtr<Asset> EditorAssetManager::CreateAsset(const AssetMetaData& metaData)
{
    SharedPtr<Asset> asset;
    bool result = false;
    switch(metaData.type)
    {
        case AssetType::MODEL:
        {
            SharedPtr<ModelAsset> model = MakeShared<ModelAsset>();
            result = ModelImporter::Importe(metaData.path, *model);
            asset = model;
            break;
        }
        case AssetType::SHADER:
        {
            SharedPtr<ModelAsset> model = MakeShared<ModelAsset>();
            result = ModelImporter::Importe(metaData.path, *model);
            asset = model;
            break;
        }
        case AssetType::SCENE:
            break;
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



    if(result)
    {
        return asset;
    }

    CORE_LOG_ERROR("could not create asset with meta data id %s", metaData.id);
    return {};
}

WeakPtr<AssetMetaData> EditorAssetManager::GetMetaData(AssetID id)
{
    if(IsMetaDataAssetValid(id))
    {
        return m_metaDataRegistry[id];
    }

    CORE_LOG_ERROR("could not find asset meta data id %d", id);
    return {};
}

WeakPtr<AssetMetaData> EditorAssetManager::CreateMetaData(const Path& path)
{
    SharedPtr<AssetMetaData> metaData = MakeShared<AssetMetaData>();
    metaData->path = path;

    if(FileSystem::HasExtension(path, "fbx"))
    {
        metaData->type = AssetType::MODEL;
    }
    else if(FileSystem::IsFolder(path))
    {
        metaData->type = AssetType::FOLDER;
    }
    else if(FileSystem::HasExtension(path, "glsl"))
    {
        metaData->type = AssetType::SHADER;
    }

    metaData->id = ++assetID;

    Path metaPath = path;
    FileSystem::ReplaceExtension(metaPath, s_metaExtention);
    if(ProjectSerializer::Serialize(*metaData, metaPath))
    {
        m_metaDataRegistry[metaData->id] = metaData;
        return metaData;
    }

    CORE_LOG_ERROR("could not create asset at path %s", path.string().c_str());
    return {};
}

WeakPtr<AssetMetaData> EditorAssetManager::LoadMetaData(const Path& path)
{
    SharedPtr<AssetMetaData> metaData = MakeShared<AssetMetaData>();

    if(ProjectSerializer::Deserialize(*metaData, path))
    {
        m_metaDataRegistry[metaData->id] = metaData;
        return metaData;
    }

    CORE_LOG_ERROR("could not load asset at path %s", path.string().c_str());
    return {};
}

} // namespace WB
