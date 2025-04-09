#pragma once
#include "Core/Core.hpp"

namespace WB
{

struct Vertex3D;
template<typename TVertex>
class VertexArrayBuffer;

template<typename TIndex>
class IndexBuffer;

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
    virtual void Draw(SharedPtr<VertexArrayBuffer<Vertex3D>>& vertexArray, SharedPtr<IndexBuffer<uint32_t>>& indexBuffer) = 0;
    virtual void SetClearColor(float r, float g, float b) = 0;
    virtual void Clear() = 0;

    static UniquePtr<RendererAPI> CreateRendererAPI(API api);

    [[nodiscard]] WB_INLINE API GetAPI() { return m_api; }

private:
    API m_api;
};

}
