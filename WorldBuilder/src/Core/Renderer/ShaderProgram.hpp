#pragma once
#include "Core/Renderer/Shader.hpp"

namespace WB
{

class ShaderProgram
{
public:
    virtual ~ShaderProgram() = default;
    virtual void DestroyProgram() = 0;
    virtual void BindProgram() = 0;
    virtual void AttachShader(const Shader& shader) = 0;
    virtual void DetachShader(const Shader& shader) = 0;

    static SharedPtr<ShaderProgram> Create();
};

}
