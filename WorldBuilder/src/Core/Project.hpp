#pragma once
#include "Core/Core.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/AssetManager/EditorAssetManager.hpp"
#include "Core/AssetManager/RuntimeAssetManager.hpp"

namespace WB
{

struct ProjectSettings
{
    std::string projectName = "Empty Project";
    Path projectPath;
    Path projectAssetPath;
};

class Project
{
public:
    Project() = default;

    WB_INLINE void SetSettings(const ProjectSettings& data) { m_settings = data; }
    WB_INLINE const ProjectSettings& GetSettings() const { return m_settings; }
    WB_INLINE static SharedPtr<Project> GetActive() { return s_active; }

    WB_INLINE static SharedPtr<Project> CreateProject(const Path& path, const std::string& name)
    {
        if(FileSystem::SyncWriteAtPathAsString(path / name, name))
        {
            SharedPtr<Project> newProj = MakeShared<Project>();
            newProj->m_settings.projectName = name;
            newProj->m_settings.projectAssetPath = path;
            newProj->m_settings.projectAssetPath = path / "assets";
            return newProj;
        }
        return nullptr;
    }

    WB_INLINE static void SetActiveProject(SharedPtr<Project>& project)
    {
        s_active = project;
    }

    WB_INLINE const Path& GetAssetPath() const
    {
        return GetSettings().projectAssetPath;
    }

    WB_INLINE const Path& GetProjectPath() const
    {
        return GetSettings().projectPath;
    }

    WB_INLINE SharedPtr<AssetManagerBase> GetAssetManager() { return m_assetManager; }

    WB_INLINE SharedPtr<EditorAssetManager> GetEditorAssetManager()
    {
        SharedPtr<EditorAssetManager> manager = static_pointer_cast<EditorAssetManager>(m_assetManager);
        WB_CORE_ASSERT(manager, "Editor asset manager used in build");
        return manager;
    }

    WB_INLINE SharedPtr<RuntimeAssetManager> GetBuildAssetManager()
    {
        SharedPtr<RuntimeAssetManager> manager = static_pointer_cast<RuntimeAssetManager>(m_assetManager);
        WB_CORE_ASSERT(manager, "Build asset manager used in editor");
        return manager;
    }

private:
    ProjectSettings m_settings;
    SharedPtr<AssetManagerBase> m_assetManager;

    WB_INLINE static SharedPtr<Project> s_active;
};

}
