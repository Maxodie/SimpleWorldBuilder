#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/Serializer/ProjectSerializer.hpp"
#include "Core/Project.hpp"
#include "Core/Core.hpp"

namespace WB
{

using SceneIndex = size_t;

struct SceneBuildRegistry
{
    std::vector<AssetID> sceneIDs;
    SceneIndex AddScene(AssetID sceneAssetID)
    {
        sceneIDs.push_back(sceneAssetID);
        SceneBuildIndexSerializer::Serialize(*this, Project::GetActive()->GetSettings().settingsPath);
        return sceneIDs.size() - 1;
    }

    void RemoveScene(SceneIndex sceneIndex)
    {
        sceneIDs.erase(sceneIDs.begin() + sceneIndex);
        SceneBuildIndexSerializer::Serialize(*this, Project::GetActive()->GetSettings().settingsPath);
    }

    const ScenePackageRegistry& Get() const
    {
        return Project::GetActive()->GetAssetManager()->GetPackages();
    }
};

class SceneManagement
{
public:
    WB_INLINE bool IsValidBuildSceneID(SceneIndex id)
    {
        //SceneIndex is uint64_t so it's bigger than 0
        return id < m_sceneBuildRegistry.sceneIDs.size();
    }

    WeakPtr<class Scene3D> SwitchScene(SceneIndex sceneID);
    WeakPtr<class Scene3D> SwitchSceneByPackage(const ScenePackage& sceneAsset);
    WeakPtr<class Scene3D> SwitchSceneByAssetID(AssetID sceneAsset);

    static WB_INLINE constexpr SceneManagement& Get()
    {
        if(!s_instance)
        {
            Create();
        }

        return *s_instance;
    }

    WB_INLINE SceneBuildRegistry& GetRegistry() { return m_sceneBuildRegistry; }

private:
    static WB_INLINE SceneManagement& Create()
    {
        s_instance = new SceneManagement();

        if(!SceneBuildIndexSerializer::Deserialize(s_instance->m_sceneBuildRegistry, Project::GetActive()->GetSettings().settingsPath))
        {
            CORE_LOG_SUCCESS("could not load scene build registry");
        }

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
