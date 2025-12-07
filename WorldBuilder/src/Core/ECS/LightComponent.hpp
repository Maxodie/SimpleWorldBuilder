#pragma once

#include "Core/ECS/TransformComponent.hpp"
namespace WB
{

class PointLightComponent
{
public:
    PointLightComponent() = default;
    PointLightComponent(PointLightComponent&) = default;
    ~PointLightComponent() = default;

    WB_INLINE const glm::vec4& GetColor() const { return m_color; }
    WB_INLINE void SetColor(const glm::vec4& color) { m_color = color; }

private:
    glm::vec4 m_color{100.f, 100.f, 100.f, 255.f};
};

}
