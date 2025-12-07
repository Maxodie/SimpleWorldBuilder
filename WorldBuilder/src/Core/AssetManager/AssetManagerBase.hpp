#pragma once

#include "Core/AssetManager/Asset.hpp"
#include "Core/Core.hpp"

namespace WB
{

using PackageID = uint64_t;

class AssetManagerBase
{
public:
    AssetManagerBase() = default;
    virtual ~AssetManagerBase() = default;

    WB_FORCEINLINE virtual bool IsAssetValid(AssetID id) const
    {
        return m_registry.find(id) != m_registry.end() && id != EMPTY_ASSET;
    }

    template<typename TAsset = Asset>
    WB_FORCEINLINE WeakPtr<TAsset> GetAsset(AssetID id)
    {
        WeakPtr<Asset> asset = GetAsset(id).lock();
        if(asset.lock())
        {
            return static_pointer_cast<TAsset>(asset.lock());
        }
        CORE_LOG_ERROR("asset does not exist");
        return {};
    }

    virtual WeakPtr<Asset> GetAsset(AssetID id) = 0;
    virtual void UnloadAsset(AssetID id);
    virtual void ClearRegistry();

    WB_INLINE ScenePackageRegistry& GetPackages()
    {
        return m_packages;
    }

    WB_INLINE const ScenePackageRegistry& GetPackages() const
    {
        return m_packages;
    }

    WB_INLINE WeakPtr<ScenePackage> GetPackage(AssetID sceneID)
    {
        for(auto& scenePackage : m_packages)
        {
            if(scenePackage->GetScene() == sceneID)
            {
                return scenePackage;
            }
        }

        return {};
    }

    void AddPackage(SharedPtr<ScenePackage>& package);

    void ReplaceOrAddPackage(SharedPtr<ScenePackage>& package);
    void RemovePackage(AssetID sceneID);

    void LoadPackages();

    virtual bool CheckPackagesValidity();

protected:
    std::unordered_map<AssetID, SharedPtr<Asset>> m_registry;
    WB_INLINE static AssetID s_maxAssetID = EMPTY_ASSET;

    ScenePackageRegistry m_packages;
};

}
