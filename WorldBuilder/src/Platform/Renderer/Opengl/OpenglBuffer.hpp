#pragma once
#include "Core/Renderer/Buffer.hpp"
#include <glad/glad.h>

namespace WB
{

template<typename TVertex>
class OpenglVertexBuffer : public VertexBuffer<TVertex>
{
public:
    OpenglVertexBuffer() = delete;
    OpenglVertexBuffer(size_t startBufferCount);
    virtual ~OpenglVertexBuffer();

    WB_INLINE virtual void BindBuffer() override
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    }

    WB_INLINE virtual void UpdateData() override
    {
        BindBuffer();
        glBufferSubData(GL_ARRAY_BUFFER, 0, Buffer<TVertex>::GetCount() * sizeof(TVertex), Buffer<TVertex>::GetValues());
    }

private:
    uint32_t m_vertexBuffer;
};

template<typename TIndex>
class OpenglIndexBuffer : public IndexBuffer<TIndex>
{
public:
    OpenglIndexBuffer() = delete;
    OpenglIndexBuffer(size_t startBufferCount);
    ~OpenglIndexBuffer();

    WB_INLINE virtual void BindBuffer() override
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    }

    WB_INLINE virtual void UpdateData() override
    {
        BindBuffer();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Buffer<TIndex>::GetCount() * sizeof(TIndex), Buffer<TIndex>::GetValues());
    }

private:
    uint32_t m_indexBuffer;
};

}
