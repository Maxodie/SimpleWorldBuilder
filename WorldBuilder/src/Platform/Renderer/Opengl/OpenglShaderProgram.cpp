#include "Platform/Renderer/Opengl/OpenglShaderProgram.hpp"
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
    Link();
}

void OpenglShaderProgram::DetachShader(const Shader& shader)
{
    glDetachShader(m_programID, shader.GetShaderID());
    Link();
}

void OpenglShaderProgram::Link()
{
    glLinkProgram(m_programID);

    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
        CORE_LOG_ERROR("failed to link the shader program : %s", infoLog);
    }
}

}
