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

    WB_INLINE virtual void SetFloat(std::string name, float value) = 0;
    WB_INLINE virtual void SetFloat2(std::string name, const glm::vec2& value) = 0;
    WB_INLINE virtual void SetFloat3(std::string name, const glm::vec3& value) = 0;
    WB_INLINE virtual void SetFloat4(std::string name, const glm::vec4& value) = 0;
    WB_INLINE virtual void SetInt(std::string name, int value) = 0;
    WB_INLINE virtual void SetMat4(std::string name, const glm::mat4& value) = 0;

    static SharedPtr<ShaderProgram> Create();
};

}
