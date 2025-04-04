#pragma once
#include "Core/Renderer/VertexBuffer.hpp"
#include "Core/Renderer/Model.hpp"

namespace WB
{

class Renderer3D
{
public:
    struct RenderData
    {
        size_t MaxQuad = 10000;
        size_t MaxIndex = MaxQuad * 6;
        SharedPtr<VertexBuffer<Vertex3D>> m_vertexBuffer;
    };

public:
    static void Init();
    static void Shutdown();
    static void DrawModel(Model& model);
    static void Flush();

private:
    static RenderData m_renderData;
};

}
