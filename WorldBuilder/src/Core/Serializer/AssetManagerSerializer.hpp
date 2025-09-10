#pragma once
#include "Core/AssetManager/EditorAssetManager.hpp"

namespace WB
{

class AssetManagerSerializer
{
public:
    static bool Serialize(const struct AssetMetaData& metaData, const Path& path);
    static bool Deserialize(AssetMetaData& metaData, const Path& path);

    static bool Serialize(const MetaDataRegistry& metaDataRegistry, const Path& path);
    static bool Deserialize(MetaDataRegistry& metaDataRegistry, const Path& path);
};

}
