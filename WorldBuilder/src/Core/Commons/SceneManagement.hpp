#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/Core.hpp"

namespace WB
{

using SceneIndex = uint64_t;

struct SceneBuildRegistry
{
    std::vector<AssetID> SceneIDs;
};

class SceneManagement
{
public:
    WB_INLINE bool IsValidBuildSceneID(SceneIndex id)
    {
        //SceneIndex is uint64_t so it's bigger than 0
        return id < m_sceneBuildRegistry.SceneIDs.size();
    }

    WeakPtr<class Scene3D> SwitchScene(SceneIndex sceneID);
    WeakPtr<class Scene3D> SwitchSceneByAssetID(AssetID sceneAssetID);

    static WB_INLINE constexpr SceneManagement& Get()
    {
        if(!s_instance)
        {
            Create();
        }

        return *s_instance;
    }

private:
    static WB_INLINE SceneManagement& Create()
    {
        s_instance = new SceneManagement();
        CORE_LOG_SUCCESS("scene management created");
        return *s_instance;
    }

private:
    static SceneManagement* s_instance;

    SceneIndex m_currentIndex;
    SceneBuildRegistry m_sceneBuildRegistry;
    WeakPtr<Scene3D> m_activeScene;
};

}
