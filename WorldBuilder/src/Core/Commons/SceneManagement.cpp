#include "Core/Commons/SceneManagement.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/Project.hpp"

namespace WB
{

SceneManagement* SceneManagement::s_instance = nullptr;

WeakPtr<Scene3D> SceneManagement::SwitchScene(SceneIndex sceneID)
{
    if(m_currentIndex == sceneID)
    {
        return m_activeScene;
    }

    if(IsValidBuildSceneID(sceneID))
    {
        return {};
    }

    AssetID newSceneID = m_sceneBuildRegistry.sceneIDs[sceneID];

    WeakPtr<ScenePackage> weakPackage = Project::GetActive()->GetAssetManager()->GetPackage(newSceneID);
    if(weakPackage.lock())
    {
        SwitchSceneByPackage(*weakPackage.lock());
    }

    WeakPtr<Scene3D> scene = {};
    if(scene.lock())
    {
        m_currentIndex = sceneID;
    }

    return scene;
}

WeakPtr<Scene3D> SceneManagement::SwitchSceneByPackage(const ScenePackage& package)
{
    if(!m_activeScene.lock())
    {
        WeakPtr<Scene3D> scene = Project::GetActive()->GetAssetManager()->GetAsset<Scene3D>(package.GetScene());
        if(!scene.lock())
        {
            CORE_LOG_ERROR("try to switch scene with an invalid scene asset : %d", package.GetScene());
            return {};
        }

        m_activeScene = scene;
    }
    else
    {
        if(package.GetScene() != m_activeScene.lock()->id)
        {
            m_activeScene = m_activeScene.lock()->TransitionToNewPackage(package);
        }
    }

    return m_activeScene;
}

WeakPtr<Scene3D> SceneManagement::SwitchSceneByAssetID(AssetID sceneAsset)
{
    WeakPtr<ScenePackage> package = Project::GetActive()->GetAssetManager()->GetPackage(sceneAsset);

#ifdef WB_EDITOR
    if(!package.lock())
    {
        CORE_LOG_WARNING("trying to load the package by loading the asset");

        //load package by loading the asset and retry
        WeakPtr<Scene3D> scene = Project::GetActive()->GetAssetManager()->GetAsset<Scene3D>(sceneAsset);
        package = Project::GetActive()->GetAssetManager()->GetPackage(sceneAsset);
    }
#endif

    if(package.lock())
    {
        return SwitchSceneByPackage(*package.lock());
    }

    CORE_LOG_ERROR("No valid scene package");

    return {};
}

}
