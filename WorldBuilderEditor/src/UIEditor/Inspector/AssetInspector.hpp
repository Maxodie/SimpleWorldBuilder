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

private:
    static void TextureSelection(std::function<void(WeakPtr<Texture2D>)> textureSelectedCallback, Application& context);
    static void ShaderSelection(std::function<void(WeakPtr<Shader>)> shaderSelectedCallback, Application& context);

    template<typename TAsset = Asset>
    static WeakPtr<TAsset> AssetSelectionCheck(AssetID id)
    {
        if(id == EMPTY_ASSET)
        {
            return {};
        }
        else
        {
            return Project::GetActive()->GetAssetManager()->GetAsset<TAsset>(id);
        }
    }

    static std::string GetTextureName(WeakPtr<Texture2D> texture);
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
