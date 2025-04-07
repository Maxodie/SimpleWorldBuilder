#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/ShaderProgram.hpp"

namespace WB
{

Renderer3D::RenderData Renderer3D::m_renderData {};

void Renderer3D::Init()
{
    m_renderData.VertexBuffer = VertexBuffer<Vertex3D>::Create(m_renderData.MaxQuad);
    m_renderData.IndexBuffer = IndexBuffer<uint32_t>::Create(m_renderData.MaxIndex);

    //SHADERS
    m_renderData.VertexShader = Shader::Create();
    m_renderData.VertexShader->LoadShader(ShaderType::VERTEX, "WorldBuilderEditor/assets/VertexShader.glsl");
    m_renderData.VertexShader->CompileShader();

    m_renderData.FragmentShader = Shader::Create();
    m_renderData.FragmentShader->LoadShader(ShaderType::FRAGMENT, "WorldBuilderEditor/assets/FragmentShader.glsl");
    m_renderData.FragmentShader->CompileShader();

    m_renderData.ShaderProgram = ShaderProgram::Create();
    m_renderData.ShaderProgram->AttachShader(*m_renderData.VertexShader);
    m_renderData.ShaderProgram->AttachShader(*m_renderData.FragmentShader);
    //SHADERS

    CORE_LOG_SUCCESS("Renderer3D has been Initialized");
}

void Renderer3D::Shutdown()
{
    m_renderData.VertexShader->UnLoadShader();
    m_renderData.FragmentShader->UnLoadShader();
    CORE_LOG_SUCCESS("Renderer3D has been shutted down");
}

void Renderer3D::BeginScene()
{

}

void Renderer3D::EndScene()
{
    Flush();
}

void Renderer3D::DrawModel(Model& model)
{
    if(m_renderData.MaxQuad - m_renderData.VertexBuffer->GetCount() < model.m_verticies.size())
    {
        Flush();
    }


    for(auto& vertex : model.m_verticies)
    {
        m_renderData.VertexBuffer->AddValue(vertex);
    }

    for(auto& index : model.m_indices)
    {
        m_renderData.IndexBuffer->AddValue(index);
    }
}

void Renderer3D::Flush()
{
    m_renderData.ShaderProgram->BindProgram();

    RenderCommand::Draw(m_renderData.VertexBuffer, m_renderData.IndexBuffer);
    m_renderData.VertexBuffer->ResetBuffer();
    m_renderData.IndexBuffer->ResetBuffer();
}

}
