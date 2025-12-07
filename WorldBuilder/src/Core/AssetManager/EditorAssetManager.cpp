#include "Core/AssetManager/EditorAssetManager.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/AssetManager/Importer/ModelImporter.hpp"
#include "Core/Commons/Scene.hpp"
#include "Core/Renderer/Material.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Serializer/AssetManagerSerializer.hpp"
#include "Core/Project.hpp"
#include "Core/Serializer/MaterialSerializer.hpp"
#include "Core/Serializer/SceneSerializer.hpp"
#include "Core/Utils/FileSystem.hpp"

namespace WB
{

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
            WeakPtr<Asset> asset = LoadAsset(*metaData.lock());
            if(asset.lock())
            {
                return asset;
            }

        }
    }

    CORE_LOG_ERROR("could not find asset id %d", id);
    return {};
}

WeakPtr<Asset> EditorAssetManager::LoadAsset(const AssetMetaData& metaData)
{
    SharedPtr<Asset> asset;
    switch(metaData.type)
    {
        case AssetType::MODEL:
        {
            SharedPtr<ModelAsset> model = MakeShared<ModelAsset>();
            ModelImporter::Importe(metaData.path, *model);
            asset = model;
            break;
        }
        case AssetType::SHADER:
        {
            SharedPtr<Shader> shader = Shader::Create();
            shader->LoadShader(metaData.path);
            shader->CompileShader();
            asset = shader;
            break;
        }
        case AssetType::SCENE:
        {
            SharedPtr<Scene3D> scene = MakeShared<Scene3D>();
            SceneSerializer::Deserialize(*scene, metaData.path, true);
            asset = scene;
            break;
        }
        case AssetType::TEXTURE2D:
        {
            SharedPtr<Texture2D> texture = Texture2D::CreateTexture(metaData.path);
            asset = texture;
            break;
        }
        case AssetType::MATERIAL:
        {
            SharedPtr<Material> material = MakeShared<Material>();
            MaterialSerializer::Deserialize(*material, metaData.path);
            asset = material;
            break;
        }
        case AssetType::FOLDER:
            return {};
            break;
        case AssetType::UNKNOWN:
            break;
        default:
            break;
    }

    if(asset)
    {
        CORE_LOG_DEBUG("Asset id %d loaded", metaData.id);
        asset->id = metaData.id;
        asset->type = metaData.type;

        m_registry[asset->id] = asset;
        return asset;
    }

    CORE_LOG_ERROR("could not load asset with meta data id %s", metaData.id);
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

    if(FileSystem::HasAnyExtension(path, s_modelExtensions, 2))
    {
        metaData->type = AssetType::MODEL;
        metaData->id = ++s_maxAssetID;
        CORE_LOG_DEBUG("id model : %zu", s_maxAssetID);
    }
    else if(FileSystem::IsFolder(path))
    {
        metaData->type = AssetType::FOLDER;
        metaData->id = ++s_maxAssetID;
    }
    else if(FileSystem::HasExtension(path, ".glsl"))
    {
        metaData->type = AssetType::SHADER;
        metaData->id = ++s_maxAssetID;
        CORE_LOG_DEBUG("id shader : %zu", s_maxAssetID);
    }
    else if(FileSystem::HasExtension(path, s_materialExtension))
    {
        metaData->type = AssetType::MATERIAL;
        Material material;
        MaterialSerializer::Deserialize(material, path);
        CORE_LOG_DEBUG("id Material : %zu", material.id);
        metaData->id = material.id;
    }
    else if(FileSystem::HasAnyExtension(path, s_textureExtensions, s_textureExtensionsCount))
    {
        metaData->type = AssetType::TEXTURE2D;
        metaData->id = ++s_maxAssetID;
        CORE_LOG_DEBUG("id texture : %zu", s_maxAssetID);
    }
    else if(FileSystem::HasExtension(path, s_sceneExtension))
    {
        metaData->type = AssetType::SCENE;
        Scene3D scene;
        SceneSerializer::Deserialize(scene, path, false);
        CORE_LOG_DEBUG("id scene : %zu", scene.id);
        metaData->id = scene.id;
    }

    metaData->name = path.filename().string();


    Path metaPath = path;
    ConvertToMetaPath(metaPath);
    if(AssetManagerSerializer::Serialize(*metaData, metaPath))
    {
        m_metaDataRegistry[metaData->id] = metaData;
        Project::GetActive()->GetEditorAssetManager()->SaveAllProjectMetaData();

        return metaData;
    }

    CORE_LOG_ERROR("could not create asset at path %s", path.string().c_str());
    return {};
}

void EditorAssetManager::DeleteMeta(WeakPtr<AssetMetaData> meta)
{
    if(meta.lock())
    {
        FileSystem::Delete(meta.lock()->path);
        Path metaPath = meta.lock()->path;
        ConvertToMetaPath(metaPath);
        FileSystem::Delete(metaPath);
    }
}

WeakPtr<AssetMetaData> EditorAssetManager::LoadMetaData(const Path& path)
{
    SharedPtr<AssetMetaData> metaData = MakeShared<AssetMetaData>();

    if(AssetManagerSerializer::Deserialize(*metaData, path))
    {
        m_metaDataRegistry[metaData->id] = metaData;
        return metaData;
    }

    CORE_LOG_ERROR("could not load meta data asset at path %s", path.string().c_str());
    return {};
}

void EditorAssetManager::LoadAllProjectMetaData()
{
    if(!AssetManagerSerializer::Deserialize(m_metaDataRegistry, Project::GetActive()->GetSettings().projectMetaListPath))
    {
        return;
    }

    AssetID maxId = EMPTY_ASSET;
    for(const auto& [key, metaData] : m_metaDataRegistry)
    {
        if(maxId < key)
        {
            maxId = key;
        }
    }

    s_maxAssetID = maxId;
}

void EditorAssetManager::SaveAllProjectMetaData()
{
    if(!AssetManagerSerializer::Serialize(m_metaDataRegistry, Project::GetActive()->GetSettings().projectMetaListPath))
    {
        CORE_LOG_ERROR("Fail to serialize project meta data list");
    }
}

bool EditorAssetManager::CheckPackagesValidity()
{
    bool isValid = true;
    for(size_t i = 0; i < m_packages.size(); i++)
    {
        bool isValid = IsMetaDataAssetValid(m_packages[i]->GetScene());
        if(!isValid)
        {
            RemovePackage(m_packages[i]->GetScene());
            isValid = false;
            i--;
        }
    }

    return isValid;
}

void EditorAssetManager::HandleAssetCreationByType(AssetType type, const SharedPtr<Asset>& asset, const Path& path, const std::string& name)
{
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
            SceneSerializer::Serialize(*static_pointer_cast<Scene3D>(asset), path / fullName);
            break;
        }
        case AssetType::TEXTURE2D:
            break;
        case AssetType::MATERIAL:
        {
            std::string fullName = name + s_materialExtension;
            MaterialSerializer::Serialize(*static_pointer_cast<Material>(asset), path / fullName);
            break;
        }
        case AssetType::FOLDER:
            break;
        case AssetType::UNKNOWN:
            break;
        default:
            break;
    }
}

} // namespace WB
