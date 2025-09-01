#pragma once

#include "Core/Utils/FileSystem.hpp"
#include "Core/AssetManager/Asset.hpp"
namespace WB
{

class ModelImporter
{
public:
    static bool Importe(const Path& path, ModelAsset& modelAsset);
};

}
