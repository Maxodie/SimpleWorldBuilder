#include "Core/AssetManager/EditorAssetManager.hpp"

namespace WB
{

SharedPtr<Asset> EditorAssetManager::GetAsset(AssetID id)
{
    if(IsAssetValid(id))
    {

    }
    else if(IsMetaDataAssetValid(id))
    {

    }
    return nullptr;
}

}

