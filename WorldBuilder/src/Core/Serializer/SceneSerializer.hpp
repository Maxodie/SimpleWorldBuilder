#pragma once

#include "Core/Core.hpp"
namespace WB
{

class SceneSerializer
{
public:
    SceneSerializer() = delete;

    static bool Serialize(const class Scene3D& scene, const Path& path);
    static bool Deserialize(Scene3D& scene, const Path& path, bool loadLinkedAssets = true);
};

}
