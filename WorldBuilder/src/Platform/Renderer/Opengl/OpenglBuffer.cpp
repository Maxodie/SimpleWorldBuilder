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
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, startBufferCount * sizeof(TVertex), Buffer<TVertex>::GetValues(), GL_STATIC_DRAW);
}

template<typename TVertex>
void OpenglVertexBuffer<TVertex>::BindBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, Buffer<TVertex>::GetCount() * sizeof(TVertex), Buffer<TVertex>::GetValues());
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

template<typename TIndex>
void OpenglIndexBuffer<TIndex>::BindBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Buffer<TIndex>::GetCount() * sizeof(TIndex), Buffer<TIndex>::GetValues());
}

template class OpenglIndexBuffer<uint32_t>;

}
