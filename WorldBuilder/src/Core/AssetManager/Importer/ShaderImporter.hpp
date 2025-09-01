#pragma once
#include "Core/Renderer/Shader.hpp"
#include "Core/Utils/FileSystem.hpp"
#include "Core/AssetManager/Asset.hpp"

namespace WB
{

class ShaderImporter
{
public:
    static bool Importe(const Path& path, Shader& modelAsset);
};

}
