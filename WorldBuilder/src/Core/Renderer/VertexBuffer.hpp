#pragma once
#include "Core/Core.hpp"
#include "Core/Renderer/RendererAPI.hpp"

namespace WB
{

template<typename TVertex>
class VertexBuffer
{
public:
    VertexBuffer() = delete;
    VertexBuffer(size_t startBufferSize);

    ~VertexBuffer();

    void AddVertex(TVertex& vertex);
    virtual void BindBuffer() = 0;

    [[nodiscard]] WB_INLINE constexpr size_t GetSize() const noexcept
    {
        return m_verticiesCount;
    }

    static SharedPtr<VertexBuffer<TVertex>> Create(size_t bufferSize);

protected:
    TVertex* m_vertices;
    size_t m_verticiesCount;
};

}
