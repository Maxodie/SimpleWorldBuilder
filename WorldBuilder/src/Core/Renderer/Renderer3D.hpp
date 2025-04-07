#pragma once
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Model.hpp"
#include "Core/Renderer/ShaderProgram.hpp"

namespace WB
{

class Renderer3D
{
public:
    struct RenderData
    {
        size_t MaxQuad = 10000;
        size_t MaxIndex = MaxQuad * 6;
        SharedPtr<VertexBuffer<Vertex3D>> VertexBuffer;
        SharedPtr<IndexBuffer<uint32_t>> IndexBuffer;

        SharedPtr<ShaderProgram> ShaderProgram;
        SharedPtr<Shader> VertexShader;
        SharedPtr<Shader> FragmentShader;
    };

public:
    static void Init();
    static void Shutdown();

    static void BeginScene();
    static void EndScene();

    static void DrawModel(Model& model);
    static void Flush();

private:
    static RenderData m_renderData;
};

}
