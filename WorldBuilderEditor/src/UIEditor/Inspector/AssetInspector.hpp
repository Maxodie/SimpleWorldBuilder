#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class SceneAssetInspector
{
public:
    static void Show(SharedPtr<AssetMetaData> metaData);
};

class MaterialAssetInspector
{
public:
    static void Show(SharedPtr<AssetMetaData> metaData, Application& context);
};

class Texture2DAssetInspector
{
public:
    static void Show(SharedPtr<AssetMetaData> metaData, Application& context);

private:
    static const char* FilterToChar(Texture2D::Filter textureFilter);
    static Texture2D::Filter StringToFilter(const std::string& value);
};

}
