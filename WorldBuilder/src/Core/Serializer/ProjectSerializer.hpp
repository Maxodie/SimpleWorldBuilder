#pragma once
#include "Core/Core.hpp"

namespace WB
{

class SceneBuildIndexSerializer
{
public:
    SceneBuildIndexSerializer() = delete;

    static bool Serialize(const class SceneBuildRegistry& registry, const Path& path);
    static bool Deserialize(SceneBuildRegistry& registry, const Path& path);
};

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
