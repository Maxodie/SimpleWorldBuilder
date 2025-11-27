#pragma once
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Model.hpp"
#include "Core/Renderer/ShaderProgram.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "Core/Renderer/Vertex.hpp"
#include "Core/Renderer/Texture2D.hpp"

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

        static constexpr uint32_t MaxTextureCount = 32;
        std::array<SharedPtr<Texture2D>, MaxTextureCount> Textures;
        uint32_t TextureCount = 0;
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
    static uint32_t AddDrawTexture(const SharedPtr<Texture2D>& texture);

private:
    static RenderData m_renderData;
};

}
