#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Renderer/ShaderProgram.hpp"
#include "Core/Commons/Camera.hpp"

namespace WB
{

Renderer3D::RenderData Renderer3D::m_renderData {};

void Renderer3D::Init()
{
    m_renderData.VertexArray = VertexArrayBuffer<Vertex3D>::Create();

    m_renderData.VertexBuffer = VertexBuffer<Vertex3D>::Create(m_renderData.MaxQuad);
    m_renderData.IndexBuffer = IndexBuffer<uint32_t>::Create(m_renderData.MaxIndex);

    m_renderData.VertexBuffer->SetLayout(
        {
            {"aColor", ShaderElementType::Float4},
            {"aPos", ShaderElementType::Float3},
            {"aTexCoords", ShaderElementType::Float2},
        }
    );

    m_renderData.VertexArray->AddVertexBuffer(m_renderData.VertexBuffer);

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

void Renderer3D::BeginScene(const SceneData& scene)
{
    //post cam uniform in shader
    if(scene.cam)
    {
        m_renderData.ShaderProgram->SetMat4("uViewMatrix", scene.cam->GetViewMatrix());
        m_renderData.ShaderProgram->SetMat4("uProjectionMatrix", scene.cam->GetProjectionMatrix());
    }
}

void Renderer3D::EndScene()
{
    Flush();
}

void Renderer3D::DrawModel(const Model& model, const TransformComponent& transform)
{
    m_renderData.ShaderProgram->SetMat4("uModelMat", transform.GetModelMatrix());

    for(const auto& mesh : model.Meshes)
    {
        if(m_renderData.MaxQuad - m_renderData.VertexBuffer->GetCount() < mesh.m_vertices.size() ||
        m_renderData.MaxIndex - m_renderData.IndexBuffer->GetCount() < mesh.m_indices.size())
        {
            Flush();
        }

        for(const auto& vertex : mesh.m_vertices)
        {
            m_renderData.VertexBuffer->AddValue(vertex);
        }

        for(const auto& index : mesh.m_indices)
        {
            m_renderData.IndexBuffer->AddValue(index);
        }
    }
}

void Renderer3D::Flush()
{
    m_renderData.ShaderProgram->BindProgram();

    RenderCommand::Draw(m_renderData.VertexArray, m_renderData.IndexBuffer);
    m_renderData.VertexBuffer->ResetBuffer();
    m_renderData.IndexBuffer->ResetBuffer();
}

}
