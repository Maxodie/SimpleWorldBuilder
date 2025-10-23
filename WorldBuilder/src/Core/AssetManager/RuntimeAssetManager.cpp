#include "Core/AssetManager/RuntimeAssetManager.hpp"

namespace WB
{

WeakPtr<Asset> RuntimeAssetManager::GetAsset(AssetID id)
{
    if(IsAssetValid(id))
    {
        return m_registry[id];
    }
    else
    {
        for(auto& package : m_packages)
        {
            if(package == id)
            {
                //load scene/package with id
            }
        }
    }

    CORE_LOG_ERROR("Could not find asset %zu", id);
    return {};
}

}
