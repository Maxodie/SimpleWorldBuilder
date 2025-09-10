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
    TEXTURE,
    SCENE,
};

struct Asset
{
    AssetID id = EMPTY_ASSET;
    AssetType type = AssetType::UNKNOWN;

};

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
