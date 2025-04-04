#pragma once
#include "Core/Renderer/Vertex.hpp"

namespace WB
{

struct Model
{
    std::vector<Vertex3D> m_verticies = std::vector<Vertex3D>(0);
    std::vector<uint32_t> m_indices = std::vector<uint32_t>(0);
};

class ModelLoader
{

};

}
