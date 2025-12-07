#include "Platform/Renderer/Opengl/OpenglShaderProgram.hpp"
#include "Core/Log/Log.hpp"
#include <glad/glad.h>

namespace WB
{

OpenglShaderProgram::OpenglShaderProgram()
{
    m_programID = glCreateProgram();
}

void OpenglShaderProgram::DestroyProgram()
{
    glDeleteProgram(m_programID);
}

void OpenglShaderProgram::BindProgram()
{
    glUseProgram(m_programID);
}

void OpenglShaderProgram::AttachShader(const Shader& shader)
{
    glAttachShader(m_programID, shader.GetShaderID());
    m_isReady = false;
}

void OpenglShaderProgram::DetachShader(const Shader& shader)
{
    glDetachShader(m_programID, shader.GetShaderID());
    m_isReady = false;
}

void OpenglShaderProgram::Link()
{
    glLinkProgram(m_programID);

    glGetProgramiv(m_programID, GL_LINK_STATUS, &m_success);
    if(!m_success) {
        glGetProgramInfoLog(m_programID, 512, NULL, m_infoLog);
        CORE_LOG_ERROR("failed to link the shader program : %s", m_infoLog);
    }
    else
    {
        m_isReady = true;
    }
}

}
