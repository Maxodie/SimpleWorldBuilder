#pragma once
#include "Core/Core.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/AssetManager/EditorAssetManager.hpp"
#include "Core/AssetManager/RuntimeAssetManager.hpp"
#include "Core/Serializer/ProjectSerializer.hpp"
#include "Core/Utils/FileSystem.hpp"

namespace WB
{

struct ProjectSettings
{
    std::string projectName = "New Project";
    Path projectPath;
    Path projectAssetPath;
};

struct ProjectList
{
    std::vector<std::string> names;
    std::vector<Path> paths;
};

class Project
{
public:
    Project() = delete;
    Project(const ProjectSettings& settings)
        : m_settings(std::move(settings)), m_assetManager(MakeShared<EditorAssetManager>())
    {
    }

    WB_INLINE void SetSettings(const ProjectSettings& data) { m_settings = data; }
    WB_INLINE const ProjectSettings& GetSettings() const { return m_settings; }
    WB_INLINE static SharedPtr<Project> GetActive() { return s_active; }

    static SharedPtr<Project> GetProject(const Path& path)
    {
        ProjectSettings settings;
        if(!ProjectSerializer::Deserialize(settings, path))
        {
            CORE_LOG_ERROR("failed to open project at path %s", path.string().c_str());
            return nullptr;
        }

        return MakeShared<Project>(settings);
    }

    static bool OpenProject(const Path& path)
    {
        SharedPtr<Project> project = GetProject(path);
        if(!project)
        {
            return false;
        }

        SetActiveProject(project);
        return true;
    }

    static SharedPtr<Project> CreateProject(const Path& path, const std::string& name)
    {

        std::string pathName = name;
        FileSystem::TransformNameIntoPathString(pathName);
        Path folderPath = path / pathName;

        if(FileSystem::Exists(folderPath))
        {
            CORE_LOG_ERROR("could not create new project, path already exists : %s", path.string().c_str());
            return nullptr;
        }

        std::string assetsFolder = "assets";

        ProjectSettings settings;
        settings.projectName = name;
        settings.projectPath = folderPath;
        settings.projectAssetPath = folderPath / assetsFolder;

        FileSystem::CreateFolder(path, pathName);
        FileSystem::CreateFolder(settings.projectPath, assetsFolder);

        if(!ProjectSerializer::Serialize(settings, folderPath / (pathName + ".proj")))
        {
            CORE_LOG_ERROR("failed to serialize project named %s", name.c_str());
            return nullptr;
        }

        FileSystem::GetPersistentDataPath();

        SharedPtr<Project> newProj = MakeShared<Project>(settings);
        AddProjectToProjectList(newProj);
        return newProj;
    }

    static void AddProjectToProjectList(const SharedPtr<Project> project)
    {
        std::string pathName = project->GetSettings().projectName;
        FileSystem::TransformNameIntoPathString(pathName);

        m_projectList.paths.emplace_back(project->GetSettings().projectPath / (pathName + ".proj"));
        m_projectList.names.emplace_back(project->GetSettings().projectName);

        const char* fileName = "WorldBuilder.data";
        Path persistentPath = GetPersistentProjectListPath() / fileName;

        ProjectSerializer::Serialize(m_projectList, persistentPath);
    }

    static const ProjectList& GetProjectList()
    {
        const char* fileName = "WorldBuilder.data";
        Path persistentPath = GetPersistentProjectListPath() / fileName;

        ProjectSerializer::Deserialize(m_projectList, persistentPath);
        return m_projectList;
    }

    WB_INLINE static void SetActiveProject(SharedPtr<Project>& project)
    {
        s_active = project;
        CORE_LOG_DEBUG("active project changed : %s, assets path : %s", project->GetSettings().projectName.c_str(), project->GetSettings().projectAssetPath.string().c_str());
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

    WB_INLINE static Path GetEnginePath()
    {
        return std::filesystem::current_path();
    }

    WB_INLINE static Path GetEngineDefaultRessourcesPath()
    {
        return GetEnginePath() / "DefaultRessources";
    }

    WB_INLINE static Path GetPersistentProjectListPath()
    {
        static const char* folderName = "WorldBuilder";
        Path persistentPath = FileSystem::GetPersistentDataPath();
        Path persistentFolder = persistentPath / folderName;
        if(!FileSystem::Exists(persistentFolder))
        {
            WB_CORE_ASSERT(FileSystem::CreateFolder(persistentPath, folderName), "failed to create persistent roaming folder");
        }

        return persistentFolder;
    }

private:
    ProjectSettings m_settings;
    SharedPtr<AssetManagerBase> m_assetManager;

    WB_INLINE static ProjectList m_projectList;
    WB_INLINE static SharedPtr<Project> s_active;
};

}
