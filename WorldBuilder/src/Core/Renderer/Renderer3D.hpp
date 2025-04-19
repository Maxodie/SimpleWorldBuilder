#pragma once
#include "Core/Commons/Camera.hpp"
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Model.hpp"
#include "Core/Renderer/ShaderProgram.hpp"
#include "Core/ECS/EcsComponent.hpp"
#include "Core/Renderer/Vertex.hpp"

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
        SharedPtr<VertexArrayBuffer<Vertex3D>> VertexArray;
        SharedPtr<Shader> VertexShader;
        SharedPtr<Shader> FragmentShader;
    };

public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const Camera& camera);
    static void EndScene();

    static void DrawModel(const Model& model,const TransformComponent& transform);
    static void Flush();

private:
    static RenderData m_renderData;
};

}
