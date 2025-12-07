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

    virtual void Link() override;
    WB_INLINE virtual bool IsReady() const override { return m_isReady; }

    WB_INLINE virtual void SetFloat(const std::string& name, float value) override
    {
        BindProgram();
        glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
    }

    WB_INLINE virtual void SetFloat2(const std::string& name, const glm::vec2& value) override
    {
        BindProgram();
        glUniform2f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y);
    }

    WB_INLINE virtual void SetFloat3(const std::string& name, const glm::vec3& value) override
    {
        BindProgram();
        glUniform3f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y, value.z);
    }

    WB_INLINE virtual void SetFloat4(const std::string& name, const glm::vec4& value) override
    {
        BindProgram();
        glUniform4f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y, value.z, value.w);
    }

    WB_INLINE virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) override
    {
        BindProgram();
        glUniform1fv(glGetUniformLocation(m_programID, name.c_str()), count, values);
    }

    WB_INLINE virtual void SetInt(const std::string& name, int value) override
    {
        BindProgram();
        glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
    }

    WB_INLINE virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override
    {
        BindProgram();
        glUniform1iv(glGetUniformLocation(m_programID, name.c_str()), count, values);
    }

    WB_INLINE virtual void SetMat3(const std::string& name, const glm::mat3& value) override
    {
        BindProgram();
        glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    WB_INLINE virtual void SetMat4(const std::string& name, const glm::mat4& value) override
    {
        BindProgram();
        glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    uint32_t m_programID;

    int  m_success;
    bool m_isReady = false;
    char m_infoLog[512];
};

}
