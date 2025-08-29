#pragma once
#include "Core/Core.hpp"

namespace WB
{

class ProjectSerializer
{
public:
    ProjectSerializer() = delete;

    static bool Serialize(const struct ProjectSettings& settings, Path path);
    static bool Deserialize(ProjectSettings& settings, Path path);

    static bool Serialize(const struct ProjectList& list, Path path);
    static bool Deserialize(ProjectList& list, Path path);

    static bool Serialize(const struct AssetMetaData& metaData, Path path);
    static bool Deserialize(AssetMetaData& metaData, Path path);
};

}
