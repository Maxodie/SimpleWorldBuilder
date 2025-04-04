#include "Platform/Renderer/Opengl/OpenglVertexBuffer.hpp"
#include "Core/Renderer/VertexBuffer.hpp"
#include <glad/glad.h>

namespace WB
{

static constexpr GLfloat vertexBufferData[] =  {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

template<typename TVertex>
OpenglVertexBuffer<TVertex>::OpenglVertexBuffer(size_t startBufferSize)
    : VertexBuffer<TVertex>(startBufferSize)
{
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glGenBuffers(1, &vertexBuffer);
}

template<typename TVertex>
void OpenglVertexBuffer<TVertex>::BindBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
}

template class OpenglVertexBuffer<Vertex3D>;

}
