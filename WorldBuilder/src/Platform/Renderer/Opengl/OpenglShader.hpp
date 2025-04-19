#pragma once
#include "Core/Renderer/Shader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace WB
{

class OpenglShader : public Shader
{
public:
    virtual ~OpenglShader() = default;

    virtual bool CompileShader() override;
    WB_INLINE virtual uint32_t GetShaderID() const override
    {
        return m_shaderID;
    }

private:
    virtual bool CreateShaderData() override;
    virtual void DestroyShaderData() override;

private:
    uint32_t m_shaderID;
    uint32_t m_openglShaderType;

    int  success;
    char infoLog[512];
};

}
