#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Renderer/Texture2D.hpp"
#include "Core/Renderer/ShaderProgram.hpp"

namespace WB
{

class Material : public Asset
{
public:
    Material();
    ~Material();

    void Load(WeakPtr<Shader> vertex, WeakPtr<Shader> fragment);

    // //ALBEDO
    // WB_INLINE void SetAlbedoColor(const glm::vec4& color) { m_albedoColor = color; }
    // WB_INLINE void SetAlbedoMap(WeakPtr<Texture2D> texture) { m_albedoMap = texture; }
    //
    // WB_INLINE const glm::vec4& GetAlbedoColor() const { return m_albedoColor; }
    // WB_INLINE const WeakPtr<Texture2D> GetAlbedoMap() const { return m_albedoMap; }
    //
    // //METALLIC
    // WB_INLINE void SetMetallicPercentage(float percentage) { m_metallicPercentage = percentage; }
    // WB_INLINE void SetMetallicTexture(WeakPtr<Texture2D> texture) { m_metallicMap = texture; }
    //
    // WB_INLINE float GetMetallicPercentage() const { return m_metallicPercentage; }
    // WB_INLINE const WeakPtr<Texture2D> GetMetallicMap() const { return m_metallicMap; }
    //
    // //ROUGHNESS
    // WB_INLINE void SetRoughnessPercentage(float percentage) { m_roughnessPercentage = percentage; }
    // WB_INLINE void SetRoughnessMap(WeakPtr<Texture2D> texture) { m_roughnessMap = texture; }
    //
    // WB_INLINE float GetRoughnessPercentage() const { return m_roughnessPercentage; }
    // WB_INLINE const WeakPtr<Texture2D> GetRoughnessMap() const { return m_roughnessMap; }
    //
    // //AO
    // WB_INLINE void SetAmbiantOcclusionMap(WeakPtr<Texture2D> texture) { m_ambiantOcclusionMap = texture; }
    //
    // WB_INLINE const WeakPtr<Texture2D> GetAmbiantOcclusionMap() const { return m_ambiantOcclusionMap; }

    void Bind();
    WB_INLINE CustomShaderUniformBuffer& GetCustomBufferLayout() { return m_customUniformbufferLayout; }
    WB_INLINE const CustomShaderUniformBuffer& GetCustomBufferLayout() const { return m_customUniformbufferLayout; }
    WB_INLINE WeakPtr<Shader> GetVertexShader() const { return m_vertexShader; }
    WB_INLINE WeakPtr<Shader> GetFragmentShader() const { return m_fragmentShader; }
    WB_INLINE SharedPtr<ShaderProgram> GetShaderProgram() { return m_shaderProgram; }
    WB_INLINE bool IsReady() { return m_shaderProgram && m_shaderProgram->IsReady(); }

protected:
    SharedPtr<ShaderProgram> m_shaderProgram = nullptr;
    SharedPtr<Shader> m_vertexShader = {};
    SharedPtr<Shader> m_fragmentShader = {};

    CustomShaderUniformBuffer m_customUniformbufferLayout;
//
// private:
//     glm::vec4 m_albedoColor{0, 0, 0, 1.f};
//     WeakPtr<class Texture2D> m_albedoMap;
//
//     float m_metallicPercentage = 0.5f;
//     WeakPtr<class Texture2D> m_metallicMap;
//
//     float m_roughnessPercentage = 0.5f;
//     WeakPtr<class Texture2D> m_roughnessMap;
//
//     WeakPtr<class Texture2D> m_ambiantOcclusionMap;
};

}
