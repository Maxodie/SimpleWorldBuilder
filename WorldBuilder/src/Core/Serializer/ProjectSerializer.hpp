#pragma once
#include "Core/Core.hpp"

namespace WB
{

class ProjectSerializer
{
public:
    ProjectSerializer() = delete;

    static bool Serialize(const struct ProjectSettings& settings, const Path& path);
    static bool Deserialize(ProjectSettings& settings, const Path& path);

    static bool Serialize(const struct ProjectList& list, const Path& path);
    static bool Deserialize(ProjectList& list, const Path& path);
};

}
