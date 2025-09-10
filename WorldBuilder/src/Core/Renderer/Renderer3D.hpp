#pragma once
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Model.hpp"
#include "Core/Renderer/ShaderProgram.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "Core/Renderer/Vertex.hpp"

namespace WB
{

class Renderer3D
{
public:
    struct RenderData
    {
        size_t MaxVertex = 100000;
        size_t MaxIndex = MaxVertex * 6;
        SharedPtr<VertexBuffer<Vertex3D>> VertexBuffer;
        SharedPtr<IndexBuffer<uint32_t>> IndexBuffer;
        uint32_t IndexOffset = 0;

        SharedPtr<ShaderProgram> ShaderProgram;
        SharedPtr<VertexArrayBuffer<Vertex3D>> VertexArray;
        SharedPtr<Shader> VertexShader;
        SharedPtr<Shader> FragmentShader;
    };

public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const class Camera& cam, const TransformComponent& transform);
    static void EndScene();

    static void DrawModel(const ModelComponent& model,const TransformComponent& transform);
    static void StaticDrawModel(const ModelComponent& model,const TransformComponent& transform);
    static void Flush();

private:
    static RenderData m_renderData;
};

}
