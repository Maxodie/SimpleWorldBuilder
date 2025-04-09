#include "Platform/Renderer/Opengl/OpenglShader.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/Shader.hpp"
#include <glad/glad.h>

namespace WB
{

//Vertex shader
bool OpenglShader::CompileShader()
{
    if(m_shaderData.empty() || m_shaderType == ShaderType::NONE)
    {
        CORE_LOG_ERROR("failed to compile shader. Please load it before compiling it");
        return false;
    }

    const GLchar* data = m_shaderData.c_str();
    glShaderSource(m_shaderID, 1, &data, NULL);
    glCompileShader(m_shaderID);

    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_shaderID, 512, NULL, infoLog);
        CORE_LOG_ERROR("failed to compile shader of wb_type %d : %s", m_shaderType, infoLog);
        return false;
    }

    return true;
}

bool OpenglShader::CreateShaderData()
{
    switch (m_shaderType)
    {
        case ShaderType::NONE:
            CORE_LOG_ERROR("failed to create shader. Please load it before compiling it");
            return false;
        break;
        case ShaderType::VERTEX:
            m_openglShaderType = GL_VERTEX_SHADER;
        break;
        case ShaderType::FRAGMENT:
            m_openglShaderType = GL_FRAGMENT_SHADER;
        break;
        default:
            CORE_LOG_ERROR("failed to create shader %d. Please load it before compiling it", m_shaderID);
            return false;
        break;
    }

    m_shaderID = glCreateShader(m_openglShaderType);

    CORE_LOG_SUCCESS("Shader has been created");

    return true;
}

void OpenglShader::DestroyShaderData()
{
    glDeleteShader(m_shaderID);
    m_shaderData.clear();
    m_shaderType = ShaderType::NONE;

    CORE_LOG_SUCCESS("Shader has been destroyed");
}

}
