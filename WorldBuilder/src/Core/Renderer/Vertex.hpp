#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace WB
{

struct Vertex3D
{
    Vertex3D(glm::vec3 vec)
        : Position(vec)
    {

    }

    Vertex3D(float x, float y, float z)
        : Position(x, y, z)
    {

    }
    /*glm::vec4 Color;*/
    glm::vec3 Position;
    /*glm::vec3 Scale;*/
};

}
