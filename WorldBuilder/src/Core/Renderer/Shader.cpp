#include "Core/Renderer/Shader.hpp"
#include "Core/Core.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Platform/Renderer/Opengl/OpenglShader.hpp"

namespace WB
{

bool Shader::LoadShader(const Path& shaderPath)
{
    if(!m_shaderData.empty())
    {
        DestroyShaderData();
    }

    if(!FileSystem::SyncReadAtPathAsString(shaderPath, m_shaderData))
    {
        CORE_LOG_ERROR("failed to load shader data with path : %s", shaderPath.string().c_str());
    }

    m_shaderType = ShaderType::NONE;

    size_t stringFind = m_shaderData.find("###vertex");
    if(stringFind != std::string::npos)
    {
        m_shaderType = ShaderType::VERTEX;
        m_shaderData = m_shaderData.substr(9, m_shaderData.size() - 9);
    }
    else
    {
        stringFind = m_shaderData.find("###fragment");
        if(stringFind != std::string::npos)
        {
            m_shaderType = ShaderType::FRAGMENT;
            m_shaderData = m_shaderData.substr(11, m_shaderData.size() - 11);
        }
        else
        {
            WB_CORE_ASSERT(false, "could not find shader type");
        }
    }

    CORE_LOG_SUCCESS("Shader %s has been loaded", shaderPath.string().c_str());

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
