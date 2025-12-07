#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Renderer/ShaderProgram.hpp"
#include "Core/Commons/Camera.hpp"

namespace WB
{

Renderer3D::RenderData Renderer3D::s_renderData{};
Renderer3D::LightSettings Renderer3D::s_lightSettings{};

void Renderer3D::Init()
{
    s_renderData.VertexArray = VertexArrayBuffer<Vertex3D>::Create();

    s_renderData.VertexBuffer = VertexBuffer<Vertex3D>::Create(s_renderData.MaxVertex);
    s_renderData.IndexBuffer = IndexBuffer<uint32_t>::Create(s_renderData.MaxIndex);

    s_renderData.VertexBuffer->SetLayout(
        {
            {"aPos", ShaderElementType::Float3},
            {"aNormal", ShaderElementType::Float3},
            {"aTexCoords", ShaderElementType::Float2},
        }
    );

    s_renderData.VertexArray->AddVertexBuffer(s_renderData.VertexBuffer);

    //SHADERS
    // s_renderData.VertexShader = Shader::Create();
    // s_renderData.VertexShader->LoadShader("WorldBuilderEditor/assets/VertexShader.glsl");
    // s_renderData.VertexShader->CompileShader();
    //
    // s_renderData.FragmentShader = Shader::Create();
    // s_renderData.FragmentShader->LoadShader("WorldBuilderEditor/assets/FragmentShader.glsl");
    // s_renderData.FragmentShader->CompileShader();
    //
    // s_renderData.ShaderProgram = ShaderProgram::Create();
    // s_renderData.ShaderProgram->AttachShader(*s_renderData.VertexShader);
    // s_renderData.ShaderProgram->AttachShader(*s_renderData.FragmentShader);

    //SHADERS

    //White texture
    SharedPtr<Texture2D> whiteTexture2D = Texture2D::CreateTexture(1, 1);
    uint32_t witheTexture = 0xffffffff;
    whiteTexture2D->SetData(&witheTexture, sizeof(uint32_t));
    AddDrawTexture(whiteTexture2D);

    CORE_LOG_SUCCESS("Renderer3D has been Initialized");
}

void Renderer3D::Shutdown()
{
    s_renderData.ShaderPrograms.clear();
    CORE_LOG_SUCCESS("Renderer3D has been shutted down");
}

void Renderer3D::SetupShaderProgramUniforms(SharedPtr<ShaderProgram>& shaderProgram)
{
    if(!shaderProgram)
    {
        CORE_LOG_ERROR("Given shader program is null");
        return;
    }

    int samplers[s_renderData.MaxTextureCount];
    for(uint32_t i = 0; i < s_renderData.MaxTextureCount; ++i)
    {
        samplers[i] = i;
    }

    shaderProgram->SetIntArray("Textures", samplers, s_renderData.MaxTextureCount);
    shaderProgram->SetInt("uLightCount", 0);
}

void Renderer3D::InitShaderProgram(SharedPtr<ShaderProgram>& shaderProgram)
{
    s_renderData.ShaderPrograms.push_back(shaderProgram);
}

void Renderer3D::ShutdownShaderProgram(SharedPtr<ShaderProgram>& shaderProgram)
{
    if(shaderProgram)
    {
        shaderProgram->DestroyProgram();
    }
}

void Renderer3D::BeginScene(const Camera& cam, const TransformComponent& transform)
{
    s_lightSettings.lightCount = 0;

    //post cam uniform in shader
    for(auto& program : s_renderData.ShaderPrograms)
    {
        if(program->IsReady())
        {
            program->SetMat4("uViewMatrix", cam.GetViewMatrix());
            program->SetMat4("uProjectionMatrix", cam.GetProjectionMatrix());
            program->SetFloat3("uCamPos", transform.GetPosition());
        }
    }
}

void Renderer3D::EndScene()
{
    // Flush();
}

void Renderer3D::DrawModel(const ModelComponent& model, const TransformComponent& transform)
{
    if(!model.asset.lock() || !model.material.lock())
    {
        return;
    }

    if(model.material.lock() && model.material.lock()->IsReady())
    {
        model.material.lock()->Bind();
        model.material.lock()->GetShaderProgram()->SetMat4("uModelMat", transform.GetModelMatrix());
        model.material.lock()->GetShaderProgram()->SetMat3("uNormalMat", glm::transpose(glm::inverse(glm::mat3(transform.GetModelMatrix()))));

        for(const auto& mesh : model.asset.lock()->meshes)
        {
            for(auto& vertex : mesh.m_vertices)
            {
                s_renderData.VertexBuffer->AddValue(vertex);
            }

            for(uint32_t index : mesh.m_indices)
            {
                s_renderData.IndexBuffer->AddValue(s_renderData.IndexOffset + index);
            }
            s_renderData.IndexOffset += *std::max_element(mesh.m_indices.begin(), mesh.m_indices.end());
        }

        Flush(model.material.lock()->GetShaderProgram()); //draw call for each dynamic object (only dynamic for now)
    }
}

void Renderer3D::StaticDrawModel(const ModelComponent& model,const TransformComponent& transform)
{
    WB_CORE_ASSERT(false, "Static Draw Model is not implemented yet");
}

void Renderer3D::Flush(WeakPtr<ShaderProgram> shaderProgram)
{
    if(shaderProgram.lock())
    {
        shaderProgram.lock()->BindProgram();
    }

    for(uint32_t i = 0; i < s_renderData.TextureCount; ++i)
    {
        s_renderData.Textures[i]->Bind(i);
    }

    RenderCommand::Draw(s_renderData.VertexArray, s_renderData.IndexBuffer);

    for(auto& vertexBuffer : s_renderData.VertexArray->GetLayout())
    {
        vertexBuffer->ResetBuffer();
    }

    s_renderData.IndexBuffer->ResetBuffer();
    s_renderData.IndexOffset = 0;
    s_renderData.TextureCount = 1; // 0 is white texture

    s_lightSettings.lightCount = 0;
}

void Renderer3D::AddPointLight(const PointLightComponent& lightPointComponenet, const TransformComponent& transform)
{
    for(auto& program : s_renderData.ShaderPrograms)
    {
        if(program->IsReady())
        {
            program->SetFloat3("uLights[" + std::to_string(s_lightSettings.lightCount) + "].position", transform.GetPosition());
            program->SetFloat4("uLights[" + std::to_string(s_lightSettings.lightCount) + "].color", lightPointComponenet.GetColor());
            program->SetInt("uLightCount", ++s_lightSettings.lightCount);
        }
    }
}

uint32_t Renderer3D::AddDrawTexture(const SharedPtr<Texture2D>& texture)
{
    for(uint32_t i = 0; i < s_renderData.TextureCount; ++i)
    {
        if(s_renderData.Textures[i].get() == texture.get())
        {
            return i;
        }
    }

    s_renderData.Textures[s_renderData.TextureCount] = texture;
    return s_renderData.TextureCount++;
}

}
