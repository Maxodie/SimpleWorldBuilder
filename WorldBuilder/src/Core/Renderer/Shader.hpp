#pragma once
#include "Core/Core.hpp"
#include <glm/glm.hpp>

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

    bool LoadShader(ShaderType shaderType, const Path& shaderPath);
    bool UnLoadShader();
    virtual bool CompileShader() = 0;

    WB_INLINE virtual uint32_t GetShaderID() const = 0;

    static SharedPtr<Shader> Create();

private:
    virtual bool CreateShaderData() = 0;
    virtual void DestroyShaderData() = 0;

protected:
    std::string m_shaderData;
    ShaderType m_shaderType = ShaderType::NONE;
};

}
