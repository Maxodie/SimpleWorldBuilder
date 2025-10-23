#pragma once

#include "Core/Core.hpp"
#include "Core/AssetManager/Asset.hpp"

namespace WB
{

class ScenePackageSerializer
{
public:
    ScenePackageSerializer() = delete;

    static bool Serialize(const ScenePackageRegistry& packageRegistry, const Path& path);
    static bool Deserialize(ScenePackageRegistry& packageRegistry, const Path& path);
};

}
