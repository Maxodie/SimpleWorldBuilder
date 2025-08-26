#pragma once
#include "Core/Serializer/Serializer.hpp"
#include "Core/Project.hpp"

namespace WB
{

class ProjectSerializer : Serializer
{
public:
    ProjectSerializer() = delete;

    static void Serialize(const Project& project, Path path);
    static void Deserialize(const Project& project, Path path);
};

WB_INLINE void operator>>(const YAML::Node& node, ProjectSettings& settings)
{
}

}
