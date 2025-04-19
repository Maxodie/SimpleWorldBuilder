#pragma once
#include "Core/Core.hpp"
#include "Core/ECS/EcsComponent.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include <glm/glm.hpp>

namespace WB
{

class Camera
{
public:
    void UpdateViewProjectionMatrix(float fov, float aspectRation, float near, float far);
    [[nodiscard]] WB_INLINE const glm::mat4& GetViewMatrix() const { return m_view; }
    [[nodiscard]] WB_INLINE const glm::mat4& GetProjectionMatrix() const { return m_perspective; }

private:
    float m_aspectRatio = 0;
    float m_fov = 90;
    float m_near = 90;
    float m_far = 90;
    glm::vec3 m_up;
    glm::vec3 m_forward;
    glm::mat4 m_view;
    glm::mat4 m_perspective;

    TransformComponent m_transformComp;
};

}
