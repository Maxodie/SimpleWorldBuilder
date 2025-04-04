#include "Platform/Renderer/Opengl/OpenglRendererApi.hpp"
#include "Core/Renderer/VertexBuffer.hpp"
#include "glad/glad.h"

namespace WB
{

static constexpr int Indices[] = {
    0, 2, 1,
};

OpenglRendererAPI::OpenglRendererAPI(API api)
    : RendererAPI(api)
{
}

void OpenglRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    glViewport(x, y, w, h);
}

void OpenglRendererAPI::Draw(SharedPtr<VertexBuffer<Vertex3D>>& ertexBuffer)
{
    GLuint indexBuffer;
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    ertexBuffer->BindBuffer();
    //draw
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
}

void OpenglRendererAPI::Clear(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
