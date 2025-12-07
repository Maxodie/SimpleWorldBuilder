#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/Renderer/Material.hpp"
#include "Core/ECS/TransformComponent.hpp"

namespace WB
{

struct ModelComponent
{
    WeakPtr<ModelAsset> asset;
    WeakPtr<Material> material;
};

}
