#pragma once
#include "Core/Renderer/ShaderProgram.hpp"

namespace WB
{

class OpenglShaderProgram : public ShaderProgram
{
public:
    OpenglShaderProgram();

    virtual void DestroyProgram();
    virtual void BindProgram();
    virtual void AttachShader(const Shader& shader);
    virtual void DetachShader(const Shader& shader);

    void Link();

private:
    uint32_t m_programID;

    int  success;
    char infoLog[512];
};

}
