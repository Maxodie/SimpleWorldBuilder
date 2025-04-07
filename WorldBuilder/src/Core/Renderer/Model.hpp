#pragma once
#include "Core/Renderer/Vertex.hpp"

namespace WB
{

struct Model
{
    std::vector<Vertex3D> m_verticies;
    std::vector<uint32_t> m_indices;
};

class ModelLoader
{

};

}
