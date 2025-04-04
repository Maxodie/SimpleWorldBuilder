#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Renderer/VertexBuffer.hpp"

namespace WB
{
UniquePtr<RendererAPI> RenderCommand::s_api = nullptr;

void RenderCommand::Init()
{
    s_api = RendererAPI::CreateRendererAPI(RendererAPI::API::OpenGL);

    CORE_LOG_SUCCESS("Renderer command initialized");
}

void RenderCommand::Shutdown()
{
    CORE_LOG_SUCCESS("Renderer command has been shut down");
}

void RenderCommand::BeginScene()
{

}

void RenderCommand::EndScene()
{
    Renderer3D::Flush();
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    s_api->SetViewport(x, y, w, h);
}

void RenderCommand::Draw(SharedPtr<VertexBuffer<Vertex3D>>& vertexBuffer)
{
    s_api->Draw(vertexBuffer);
}

void RenderCommand::Clear(float r, float g, float b)
{
    s_api->Clear(r, g, b);
}

}
