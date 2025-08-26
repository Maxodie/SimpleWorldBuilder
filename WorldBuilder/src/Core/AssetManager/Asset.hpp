#pragma once
#include "Core/Core.hpp"
#include "Core/Renderer/Model.hpp"

namespace WB
{

using AssetID = uint64_t;
const AssetID EMPTY_ASSET = 0u;

enum class AssetType : uint8_t
{
    UNKNOWN,
    MATERIAL,
    MODEL,
    TEXTURE,
    SCENE,
};

struct Asset
{
    AssetID id = EMPTY_ASSET;
    AssetType type = AssetType::UNKNOWN;
};

struct ModelAsset : public Asset
{
    Model data;
};

}
