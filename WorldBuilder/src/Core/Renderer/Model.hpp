#pragma once
#include "Core/Renderer/Vertex.hpp"

namespace WB
{

struct Mesh
{
    std::vector<Vertex3D> m_vertices;
    std::vector<uint32_t> m_indices;

    Mesh(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices)
        : m_vertices(vertices), m_indices(indices)
    {

    }
};

struct Model
{
    std::vector<Mesh> Meshes;

    void Load(const std::string& path);
};

}
