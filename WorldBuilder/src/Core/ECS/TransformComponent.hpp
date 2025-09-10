#pragma once
#include "Core/Commons/Scene.hpp"
#include "Core/Core.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "entt/entity/entity.hpp"
#include "glm/ext/vector_float3.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace WB
{

class TransformComponent
{
public:
    TransformComponent() = default;
    TransformComponent(TransformComponent&) = default;
    ~TransformComponent() = default;

    void UpdateModelMatrix()
    {
        m_modelMat = glm::translate(glm::mat4(1.0f), m_position);

        m_modelMat = glm::rotate(m_modelMat, m_rotation.x, glm::vec3(1,0,0));
        m_modelMat = glm::rotate(m_modelMat, m_rotation.y, glm::vec3(0,1,0));
        m_modelMat = glm::rotate(m_modelMat, m_rotation.z, glm::vec3(0,0,1));

        m_modelMat = glm::scale(m_modelMat, m_scale);
    }

    const glm::vec3& GetForward()
    {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, m_rotation.x, glm::vec3(1,0,0));
        transform = glm::rotate(transform, m_rotation.y, glm::vec3(0,1,0));
        transform = glm::rotate(transform, m_rotation.z, glm::vec3(0,0,1));

        m_forward = glm::normalize(glm::vec3(glm::inverse(transform)[2]));

        return m_forward;
    }

    const glm::vec3& GetUp()
    {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, m_rotation.x, glm::vec3(1,0,0));
        transform = glm::rotate(transform, m_rotation.y, glm::vec3(0,1,0));
        transform = glm::rotate(transform, m_rotation.z, glm::vec3(0,0,1));

        m_up = glm::normalize(glm::vec3(glm::inverse(transform)[1]));

        return m_up;
    }

    WB_INLINE const glm::vec3& GetPosition() const { return m_position; }
    WB_INLINE const glm::vec3& GetRotation() const { return m_rotation; }
    WB_INLINE const glm::vec3& GetScale() const { return m_scale; }
    WB_INLINE const glm::mat4& GetModelMatrix() const {  return m_modelMat; }

    WB_INLINE void SetPosition(const glm::vec3& position) { m_position = position; }
    WB_INLINE void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
    WB_INLINE void SetScale(const glm::vec3& scale) { m_scale = scale; }

    WB_INLINE void Translate(const glm::vec3& position) { m_position += position; }
    WB_INLINE void Rotate(const glm::vec3& rotation) { m_rotation += rotation; }

private:
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_modelMat;

    glm::vec3 m_forward;
    glm::vec3 m_up;
};

struct InfoComponent
{
    InfoComponent(EntityHandle entityHandle) : handle(entityHandle) {}
    InfoComponent(InfoComponent&) = default;
    InfoComponent() = default;
    ~InfoComponent() = default;

    EntityHandle parent = entt::null;
    std::string name = "Entity";
    EntityHandle handle;
};

}
