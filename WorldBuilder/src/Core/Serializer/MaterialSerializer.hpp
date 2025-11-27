#pragma once

#include "Core/Core.hpp"
namespace WB
{

class MaterialSerializer
{
public:
    MaterialSerializer() = delete;

    static bool Serialize(const class Material& material, const Path& path);
    static bool Deserialize(Material& material, const Path& path);
};

}
