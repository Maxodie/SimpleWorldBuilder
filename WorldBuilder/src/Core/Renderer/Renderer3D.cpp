#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Core.hpp"
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

    m_renderData.VertexBuffer = VertexBuffer<Vertex3D>::Create(m_renderData.MaxVertex);
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
    m_renderData.VertexShader->LoadShader("WorldBuilderEditor/assets/VertexShader.glsl");
    m_renderData.VertexShader->CompileShader();

    m_renderData.FragmentShader = Shader::Create();
    m_renderData.FragmentShader->LoadShader("WorldBuilderEditor/assets/FragmentShader.glsl");
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

void Renderer3D::BeginScene(const Camera& cam, const TransformComponent& transform)
{
    //post cam uniform in shader
    m_renderData.ShaderProgram->SetMat4("uViewMatrix", cam.GetViewMatrix());
    m_renderData.ShaderProgram->SetMat4("uProjectionMatrix", cam.GetProjectionMatrix());
}

void Renderer3D::EndScene()
{
    Flush();
}

void Renderer3D::DrawModel(const ModelComponent& model, const TransformComponent& transform)
{
    if(!model.asset.lock())
    {
        CORE_LOG_ERROR("model asset is not valid");
        return;
    }

    m_renderData.ShaderProgram->SetMat4("uModelMat", transform.GetModelMatrix());

    for(const auto& mesh : model.asset.lock()->meshes)
    {
        for(auto& vertex : mesh.m_vertices)
        {
            m_renderData.VertexBuffer->AddValue(vertex);
        }

        for(uint32_t index : mesh.m_indices)
        {
            m_renderData.IndexBuffer->AddValue(m_renderData.IndexOffset + index);
        }
        m_renderData.IndexOffset += *std::max_element(mesh.m_indices.begin(), mesh.m_indices.end());
    }

    Flush(); //draw call for each object bc dynamic
}

void Renderer3D::StaticDrawModel(const ModelComponent& model,const TransformComponent& transform)
{
    WB_CORE_ASSERT(false, "Static Draw Model is not implemented yet");
}

void Renderer3D::Flush()
{
    m_renderData.ShaderProgram->BindProgram();

    RenderCommand::Draw(m_renderData.VertexArray, m_renderData.IndexBuffer);

    for(auto& vertexBuffer : m_renderData.VertexArray->GetLayout())
    {
        vertexBuffer->ResetBuffer();
    }

    m_renderData.IndexBuffer->ResetBuffer();
    m_renderData.IndexOffset = 0;
}

}
