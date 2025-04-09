#include "Core/Renderer/Shader.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Platform/Renderer/Opengl/OpenglShader.hpp"

namespace WB
{

bool Shader::LoadShader(ShaderType shaderType, const char* shaderPath)
{
    if(!m_shaderData.empty())
    {
        DestroyShaderData();
    }

    m_shaderType = shaderType;

    if(!FileSystem::GetFileAsChar(shaderPath, m_shaderData))
    {
        CORE_LOG_ERROR("failed to load shader data with path : %s", shaderPath);
    }

    CORE_LOG_SUCCESS("Shader %s has been loaded", shaderPath);

    return CreateShaderData();
}

bool Shader::UnLoadShader()
{
    DestroyShaderData();
    return true;
}

SharedPtr<Shader> Shader::Create()
{

    switch(RenderCommand::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return MakeShared<OpenglShader>();
        break;

        case RendererAPI::API::None:
            CORE_LOG_ERROR("Unknown RendererAPI : %d", RenderCommand::GetAPI());
        break;

        default:
            CORE_LOG_ERROR("Unknown RendererAPI : %d", RenderCommand::GetAPI());
        break;
    }

    return nullptr;
}

}
