#pragma once
#include "Core/Renderer/RendererAPI.hpp"
#include "Core/Renderer/VertexBuffer.hpp"

namespace WB
{

class RenderCommand
{
public:
    static void Init();
    static void Shutdown();

    static void BeginScene();
    static void EndScene();
    static void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    static void Draw(SharedPtr<VertexBuffer<Vertex3D>>& vertexBuffer);
    static void Clear(float r, float g, float b);

    WB_INLINE static RendererAPI::API GetAPI() { return s_api->GetAPI(); }

private:
    static UniquePtr<RendererAPI> s_api;
};

}
