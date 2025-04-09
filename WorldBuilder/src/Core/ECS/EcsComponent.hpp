#pragma once
#include <glm/glm.hpp>

namespace WB
{

struct TransformComponent
{
    TransformComponent() = default;
    TransformComponent(TransformComponent&) = default;
    ~TransformComponent() = default;

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
};

}
