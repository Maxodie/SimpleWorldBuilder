#include "Platform/Renderer/Opengl/OpenglRendererApi.hpp"
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Vertex.hpp"
#include "glad/glad.h"

namespace WB
{

OpenglRendererAPI::OpenglRendererAPI(API api)
    : RendererAPI(api)
{
}

void OpenglRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    glViewport(x, y, w, h);
}

void OpenglRendererAPI::Draw(SharedPtr<VertexArrayBuffer<Vertex3D>>& vertexArray, SharedPtr<IndexBuffer<uint32_t>>& indexBuffer)
{
    auto& layout = vertexArray->GetLayout();
    for(const auto& buffer : layout)
    {
        buffer->UpdateData();
    }

    indexBuffer->UpdateData();

    glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, (void*)0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenglRendererAPI::SetClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
}

void OpenglRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
