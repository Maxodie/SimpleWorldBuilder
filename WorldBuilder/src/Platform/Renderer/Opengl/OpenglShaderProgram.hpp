#pragma once
#include "Core/Renderer/ShaderProgram.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace WB
{

class OpenglShaderProgram : public ShaderProgram
{
public:
    OpenglShaderProgram();

    virtual void DestroyProgram() override;
    virtual void BindProgram() override;
    virtual void AttachShader(const Shader& shader) override;
    virtual void DetachShader(const Shader& shader) override;

    void Link();

    WB_INLINE virtual void SetFloat(std::string name, float value) override
    {
        BindProgram();
        glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
    }

    WB_INLINE virtual void SetFloat2(std::string name, const glm::vec2& value) override
    {
        BindProgram();
        glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 2, glm::value_ptr(value));
    }

    WB_INLINE virtual void SetFloat3(std::string name, const glm::vec3& value) override
    {
        BindProgram();
        glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 3, glm::value_ptr(value));
    }

    WB_INLINE virtual void SetFloat4(std::string name, const glm::vec4& value) override
    {
        BindProgram();
        glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 4, glm::value_ptr(value));
    }

    WB_INLINE virtual void SetInt(std::string name, int value) override
    {
        BindProgram();
        glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
    }

    WB_INLINE virtual void SetMat4(std::string name, const glm::mat4& value) override
    {
        BindProgram();
        glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    uint32_t m_programID;

    int  success;
    char infoLog[512];
};

}
