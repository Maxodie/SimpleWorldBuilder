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

    WB_INLINE virtual void SetFloat(const std::string& name, float value) = 0;
    WB_INLINE virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
    WB_INLINE virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
    WB_INLINE virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
    WB_INLINE virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) = 0;
    WB_INLINE virtual void SetInt(const std::string& name, int value) = 0;
    WB_INLINE virtual void SetIntArray(const std::string& name, int* value, uint32_t count) = 0;
    WB_INLINE virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

    static SharedPtr<ShaderProgram> Create();
};

}
