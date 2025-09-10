#pragma once
#include "Core/Core.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include <glm/glm.hpp>

namespace WB
{

class Camera
{
public:

    Camera()
    {
        UpdateProjectionMatrix();
    }

    void SetupProjectionMatrix(float fov, float aspectRation, float near, float far);
    void UpdateProjectionMatrix();
    void UpdateViewMatrix(TransformComponent& transformComp);
    void ResizeBound(float width, float height);
    void SetFov(float fov);

    [[nodiscard]] WB_INLINE const glm::mat4& GetViewMatrix() const { return m_view; }
    [[nodiscard]] WB_INLINE const glm::mat4& GetProjectionMatrix() const { return m_perspective; }

private:
    float m_aspectRatio = 1920.f/1080.f;
    float m_fov = 80;
    float m_near = 0.1f;
    float m_far = 100.f;
    glm::vec3 m_up;
    glm::vec3 m_forward;
    glm::mat4 m_view;
    glm::mat4 m_perspective;
};

}
