#include "Core/Commons/Camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace WB
{

void Camera::SetupProjectionMatrix(float fov, float aspectRation, float near, float far)
{
    m_fov = fov;
    m_aspectRatio = aspectRation;
    m_near = near;
    m_far = far;

    UpdateProjectionMatrix();
}

void Camera::UpdateProjectionMatrix()
{
    m_perspective = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}

void Camera::UpdateViewMatrix(TransformComponent& transformComp)
{
    m_view = glm::lookAt(transformComp.GetPosition(), transformComp.GetPosition() + transformComp.GetForward(), transformComp.GetUp());
}

void Camera::ResizeBound(float width, float height)
{
    m_aspectRatio = width / height;
    UpdateProjectionMatrix();
}

void Camera::SetFov(float fov)
{
    m_fov = fov;
    UpdateProjectionMatrix();
}

}
