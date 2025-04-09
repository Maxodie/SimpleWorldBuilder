#pragma once
#include "Core/Renderer/Shader.hpp"

namespace WB
{

class OpenglShader : public Shader
{
public:
    virtual ~OpenglShader() = default;

    virtual bool CompileShader();
    WB_INLINE virtual uint32_t GetShaderID() const
    {
        return m_shaderID;
    }

private:
    virtual bool CreateShaderData();
    virtual void DestroyShaderData();

private:
    uint32_t m_shaderID;
    uint32_t m_openglShaderType;

    int  success;
    char infoLog[512];
};

}
