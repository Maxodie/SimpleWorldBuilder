#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Renderer/RenderCommand.hpp"

namespace WB
{

Renderer3D::RenderData Renderer3D::m_renderData {};

void Renderer3D::Init()
{
    m_renderData.m_vertexBuffer = VertexBuffer<Vertex3D>::Create(m_renderData.MaxQuad);
    CORE_LOG_SUCCESS("Renderer3D has been Initialized");
}

void Renderer3D::Shutdown()
{
    CORE_LOG_SUCCESS("Renderer3D has been shutted down");
}

void Renderer3D::DrawModel(Model& model)
{
    if(m_renderData.MaxQuad - m_renderData.m_vertexBuffer->GetSize() < model.m_verticies.size())
    {
        Flush();
    }

    for(auto& vertex : model.m_verticies)
    {
        m_renderData.m_vertexBuffer->AddVertex(vertex);
    }
}

void Renderer3D::Flush()
{
    RenderCommand::Draw(m_renderData.m_vertexBuffer);
}

}
