#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/Serializer/ScenePackageSerializer.hpp"
#include "Core/Project.hpp"

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

void AssetManagerBase::AddPackage(SharedPtr<ScenePackage>& package)
{
    WeakPtr<ScenePackage> found = GetPackage(package->GetScene());
    if(found.lock())
    {
        CORE_LOG_WARNING("package with sceneID %zu is already stored in the AssetManager", package->GetScene());
        return;
    }
    else
    {
        m_packages.push_back(package);
        CORE_LOG_DEBUG("Package added to the package list, id %zu", package->GetScene());
    }

    ScenePackageSerializer::Serialize(m_packages, Project::GetActive()->GetSettings().projectPackageListPath);
}

void AssetManagerBase::ReplaceOrAddPackage(SharedPtr<ScenePackage>& package)
{
    WeakPtr<ScenePackage> found = Project::GetActive()->GetAssetManager()->GetPackage(package->GetScene());
    if(found.lock())
    {
        RemovePackage(package->GetScene());
    }

    AddPackage(package);
}

void AssetManagerBase::RemovePackage(AssetID sceneID)
{
    WeakPtr<ScenePackage> found = GetPackage(sceneID);
    if(found.lock())
    {
        m_packages.erase(std::remove_if(
            m_packages.begin(), m_packages.end(),
            [&](const SharedPtr<ScenePackage>& i)
            {
                return i->GetScene() == sceneID;
            }
        ));
        CORE_LOG_DEBUG("Package removed from the package list, id %zu", sceneID);
        return;
    }
    else
    {
        CORE_LOG_WARNING("package with sceneID %zu does not exist in the AssetManager", sceneID);
    }

    ScenePackageSerializer::Serialize(m_packages, Project::GetActive()->GetSettings().projectPackageListPath);
}

void AssetManagerBase::LoadPackages()
{
    ScenePackageSerializer::Deserialize(m_packages, Project::GetActive()->GetSettings().projectPackageListPath);
    if(!CheckPackagesValidity())
    {
        ScenePackageSerializer::Serialize(m_packages, Project::GetActive()->GetSettings().projectPackageListPath);
    }
}

bool AssetManagerBase::CheckPackagesValidity()
{
    return true;
}

}
