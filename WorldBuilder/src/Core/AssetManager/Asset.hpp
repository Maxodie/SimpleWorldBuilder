#pragma once
#include "Core/Core.hpp"
#include "Core/Renderer/Vertex.hpp"

namespace WB
{

using AssetID = uint64_t;
static const AssetID EMPTY_ASSET = 0u;

enum class AssetType : uint8_t
{
    UNKNOWN,
    FOLDER,
    SHADER,
    MODEL,
    MATERIAL,
    TEXTURE2D,
    SCENE,
};

struct Asset
{
    AssetID id = EMPTY_ASSET;
    AssetType type = AssetType::UNKNOWN;

};

class ScenePackage
{
public:
    WB_INLINE const std::vector<AssetID>& GetAssets() const { return m_assets; }
    WB_INLINE AssetID GetScene() const { return m_sceneID; }

    WB_INLINE void ResizeAssetList(size_t newSize) { m_assets.resize(newSize); }

    void AddUniqueAsset(AssetID assetID)
    {
        for(AssetID id : m_assets)
        {
            if(assetID == id)
            {
                return;
            }
        }

        m_assets.push_back(assetID);
    }

    WB_INLINE void SetScene(AssetID sceneID) { m_sceneID = sceneID; }

private:
    std::vector<AssetID> m_assets;
    AssetID m_sceneID;
};

using ScenePackageRegistry = std::vector<SharedPtr<ScenePackage>>;

struct Mesh
{
    std::vector<Vertex3D> m_vertices;
    std::vector<uint32_t> m_indices;

    Mesh(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices)
        : m_vertices(vertices), m_indices(indices)
    {

    }
};

class ModelAsset : public Asset
{
public:
    std::vector<Mesh> meshes;
};

}
