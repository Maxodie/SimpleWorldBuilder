#pragma once
#include "Core/Core.hpp"

namespace WB
{

enum class ShaderType
{
    NONE,
    VERTEX,
    FRAGMENT
};

class Shader
{
public:
    virtual ~Shader() = default;

    bool LoadShader(ShaderType shaderType, const char* shaderPath);
    bool UnLoadShader();
    virtual bool CompileShader() = 0;

    WB_INLINE virtual uint32_t GetShaderID() const = 0;

    static SharedPtr<Shader> Create();

private:
    virtual void CreateShaderData() = 0;
    virtual void DestroyShaderData() = 0;

protected:
    std::string m_shaderData;
    ShaderType m_shaderType = ShaderType::NONE;
};

}
