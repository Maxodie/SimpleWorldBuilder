#include "Core/Commons/SceneManagement.hpp"
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

    AssetID newSceneID = m_sceneBuildRegistry.SceneIDs[sceneID];

    WeakPtr<Scene3D> scene = SwitchSceneByAssetID(newSceneID);
    if(scene.lock())
    {
        m_currentIndex = sceneID;
    }

    return scene;
}

WeakPtr<class Scene3D> SceneManagement::SwitchSceneByAssetID(AssetID sceneAssetID)
{
    if(!m_activeScene.lock())
    {
        WeakPtr<Scene3D> scene = Project::GetActive()->GetAssetManager()->GetAsset<Scene3D>(sceneAssetID);
        if(!scene.lock())
        {
            CORE_LOG_ERROR("try to switch scene with an invalid scene asset : %d", sceneAssetID);
            return {};
        }

        m_activeScene = scene;
    }
    else
    {
        if(sceneAssetID != m_activeScene.lock()->id)
        {
            m_activeScene = m_activeScene.lock()->TransitionToNewPackage(sceneAssetID);
        }
    }

    return m_activeScene;
}

}
