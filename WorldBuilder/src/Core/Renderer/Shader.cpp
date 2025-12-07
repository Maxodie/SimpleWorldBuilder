#include "Core/Renderer/Shader.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Utils/StringHelper.hpp"
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

    const constexpr char* vertexKey = "###vertex";
    const constexpr char* fragmentKey = "###fragment";
    m_shaderType = ShaderType::NONE;
    size_t stringFind = m_shaderData.find(vertexKey);
    if(stringFind != std::string::npos)
    {
        m_shaderType = ShaderType::VERTEX;
    }
    else
    {
        stringFind = m_shaderData.find(fragmentKey);
        if(stringFind != std::string::npos)
        {
            m_shaderType = ShaderType::FRAGMENT;
        }
    }

    const constexpr char* customKey = "###custom";
    size_t customStringFind = m_shaderData.find(customKey);
    if(customStringFind != std::string::npos)
    {
        customStringFind += strlen(customKey);
        std::string line;
        std::stringstream shaderDataStream{m_shaderData};
        shaderDataStream.seekg(customStringFind);
        while(std::getline(shaderDataStream, line, ';') && shaderDataStream.tellg() <= stringFind)
        {
            // std::vector<std::string> tokens = StringHelper::Split(line, " ");
            std::stringstream lineStream{line};
            std::string token;
            std::array<std::string, 3> tokens;
            for(int i = 0; i < 3; i++)
            {
                std::getline(lineStream, token, ' ');
                tokens[i] = token;
                tokens[i].erase(std::remove_if(tokens[i].begin(), tokens[i].end(),
                    [](char c)
                    {
                        return std::isspace(c) || c == '\n';
                    }
                ),
                tokens[i].end());
            }
            m_customUniformTemplate.AddElement(tokens[0], tokens[1], tokens[2]);
        }
    }


    switch(m_shaderType)
    {
        case ShaderType::VERTEX:
        {
            stringFind += strlen(vertexKey);
            m_shaderData = m_shaderData.substr(stringFind, m_shaderData.size() - stringFind);
            break;
        }
        case ShaderType::FRAGMENT:
        {
            stringFind += strlen(fragmentKey);
            m_shaderData = m_shaderData.substr(stringFind, m_shaderData.size() - stringFind);
            break;
        }
        case ShaderType::NONE:
        {
            WB_CORE_ASSERT(false, "could not find shader type");
            break;
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
