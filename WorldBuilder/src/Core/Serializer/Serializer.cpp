#include "Core/Serializer/Serializer.hpp"

namespace WB
{

YAML::Node Serializer::encode(const glm::vec3& rhs)
{
    YAML::Node node;
    node.push_back(rhs.x);
    node.push_back(rhs.y);
    node.push_back(rhs.z);
    return node;
}

bool Serializer::decode(const YAML::Node& node, glm::vec3& rhs)
{
    if(!node.IsSequence() || node.size() != 3)
    {
        return false;
    }

    rhs.x = node[0].as<float>();
    rhs.y = node[1].as<float>();
    rhs.z = node[2].as<float>();

    return true;
}

}
