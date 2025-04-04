#pragma once
#include "Core/Renderer/RendererAPI.hpp"

namespace WB
{

class OpenglRendererAPI : public RendererAPI
{
public:
    OpenglRendererAPI(API api);

    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
    virtual void Draw(SharedPtr<VertexBuffer<Vertex3D>>& vertexBuffer) override;
    virtual void Clear(float r, float g, float b) override;
};

}
