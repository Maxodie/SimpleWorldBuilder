#pragma once
#include "Core/Renderer/Buffer.hpp"

namespace WB
{

template<typename TVertex>
class OpenglVertexBuffer : public VertexBuffer<TVertex>
{
public:
    OpenglVertexBuffer() = delete;
    OpenglVertexBuffer(size_t startBufferCount);

    virtual void BindBuffer() override;

private:
    uint32_t m_vertexArrayID;
    uint32_t m_vertexBuffer;
};

template<typename TVertex>
class OpenglIndexBuffer : public IndexBuffer<TVertex>
{
public:
    OpenglIndexBuffer() = delete;
    OpenglIndexBuffer(size_t startBufferCount);

    virtual void BindBuffer() override;

private:
    uint32_t m_indexBuffer;
};

}
