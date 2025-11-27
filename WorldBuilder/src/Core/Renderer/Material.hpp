#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/Renderer/Texture2D.hpp"

namespace WB
{

class Material : public Asset
{
public:
    Material() = default;
    Material(const glm::vec4& color);

    WB_INLINE void SetAlbedoColor(const glm::vec4& color) { m_albedoColor = color; }
    WB_INLINE void SetTexture(WeakPtr<Texture2D> texture) { m_albedoTexture = texture; }

    WB_INLINE const glm::vec4& GetAlbedoColor() const { return m_albedoColor; }
    WB_INLINE const WeakPtr<Texture2D> GetAlbedoTexture() const { return m_albedoTexture; }
    WB_INLINE WeakPtr<Texture2D> GetAlbedoTexture() { return m_albedoTexture; }

private:
    glm::vec4 m_albedoColor{0, 0, 0, 1.f};
    WeakPtr<class Texture2D> m_albedoTexture;
};

}
