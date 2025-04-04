#pragma once
#include "Core/Core.hpp"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace WB
{

struct Vertex3D
{
    glm::vec4 Color;
    glm::vec3 Position;
    glm::vec3 Scale;
};

}
