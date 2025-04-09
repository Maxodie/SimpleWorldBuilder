#pragma once
#include "Core/Renderer/RendererAPI.hpp"

namespace WB
{

class OpenglRendererAPI : public RendererAPI
{
public:
    OpenglRendererAPI(API api);
    ~OpenglRendererAPI() = default;

    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
    virtual void Draw(SharedPtr<VertexArrayBuffer<Vertex3D>>& vertexArray, SharedPtr<IndexBuffer<uint32_t>>& indexBuffer) override;
    virtual void SetClearColor(float r, float g, float b) override;
    virtual void Clear() override;
};

}
