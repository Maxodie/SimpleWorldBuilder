#include "Core/AssetManager/AssetManagerBase.hpp"

namespace WB
{

void AssetManagerBase::UnloadAsset(AssetID id)
{
    if(IsAssetValid(id))
    {
        CORE_LOG_DEBUG("Asset manager unload asset id : %d", id);
        m_registry.erase(id);
    }
}

void AssetManagerBase::ClearRegistry()
{
    m_registry.clear();
    s_maxAssetID = EMPTY_ASSET;
}

}
