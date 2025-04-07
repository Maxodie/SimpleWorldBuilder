#pragma once
#include "Core/Renderer/RendererAPI.hpp"
#include "Core/Renderer/Buffer.hpp"

namespace WB
{

class RenderCommand
{
public:
    WB_INLINE static void Init()
    {
        s_api = RendererAPI::CreateRendererAPI(RendererAPI::API::OpenGL);

        CORE_LOG_SUCCESS("Renderer command initialized");
    }

    WB_INLINE static void Shutdown()
    {
        CORE_LOG_SUCCESS("Renderer command has been shut down");
    }

    WB_INLINE static void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
    {
        s_api->SetViewport(x, y, w, h);
    }

    WB_INLINE static void Draw(SharedPtr<VertexBuffer<Vertex3D>>& vertexBuffer, SharedPtr<IndexBuffer<uint32_t>>& indexBuffer)
    {
        s_api->Draw(vertexBuffer, indexBuffer);
    }

    WB_INLINE static void SetClearColor(float r, float g, float b)
    {
        s_api->SetClearColor(r, g, b);
    }

    WB_INLINE static void Clear()
    {
        s_api->Clear();
    }

    WB_INLINE static RendererAPI::API GetAPI() { return s_api->GetAPI(); }

private:
    static UniquePtr<RendererAPI> s_api;
};

}
