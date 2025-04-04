#pragma once
#include "Core/Core.hpp"

namespace WB
{

struct Vertex3D;
template<typename TVertex>
class VertexBuffer;

class RendererAPI
{
public:
    enum class API
    {
        None,
        OpenGL
    };

public:
    RendererAPI() = delete;
    RendererAPI(API api);

    virtual ~RendererAPI() = default;

    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
    virtual void Draw(SharedPtr<VertexBuffer<Vertex3D>>& vertexBuffer) = 0;
    virtual void Clear(float r, float g, float b) = 0;

    static UniquePtr<RendererAPI> CreateRendererAPI(API api);

    [[nodiscard]] WB_INLINE API GetAPI() { return m_api; }

private:
    API m_api;
};

}
