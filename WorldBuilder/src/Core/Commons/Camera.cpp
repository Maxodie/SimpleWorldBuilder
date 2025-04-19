#include "Core/Commons/Camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace WB
{

void Camera::UpdateViewProjectionMatrix(float fov, float aspectRation, float near, float far)
{
    m_fov = fov;
    m_aspectRatio = aspectRation;
    m_near = near;
    m_far = far;
    m_perspective = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);

    m_view = glm::lookAt(m_transformComp.GetPosition(), m_transformComp.GetPosition() + m_transformComp.GetForward(), m_transformComp.GetUp());
}

}
