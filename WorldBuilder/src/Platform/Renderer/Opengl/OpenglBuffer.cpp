#include "Platform/Renderer/Opengl/OpenglBuffer.hpp"
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Vertex.hpp"
#include <glad/glad.h>

namespace WB
{

// Vertex Buffer
template<typename TVertex>
OpenglVertexBuffer<TVertex>::OpenglVertexBuffer(size_t startBufferCount)
    : VertexBuffer<TVertex>(startBufferCount)
{
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, startBufferCount * sizeof(TVertex), Buffer<TVertex>::GetValues(), GL_STATIC_DRAW);
}

template<typename TVertex>
OpenglVertexBuffer<TVertex>::~OpenglVertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBuffer);
}

template class OpenglVertexBuffer<Vertex3D>;

// Index Buffer
template<typename TIndex>
OpenglIndexBuffer<TIndex>::OpenglIndexBuffer(size_t startBufferCount)
    : IndexBuffer<TIndex>(startBufferCount)
{
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, startBufferCount * sizeof(TIndex), Buffer<TIndex>::GetValues(), GL_STATIC_DRAW);
}

template<typename TVertex>
OpenglIndexBuffer<TVertex>::~OpenglIndexBuffer()
{
    glDeleteBuffers(1, &m_indexBuffer);
}

template class OpenglIndexBuffer<uint32_t>;

}
