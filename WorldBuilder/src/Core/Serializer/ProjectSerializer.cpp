#include "Core/Serializer/ProjectSerializer.hpp"
#include "Core/Utils/FileSystem.hpp"

namespace WB
{

void ProjectSerializer::Serialize(const Project& project, Path path)
{
    YAML::Emitter emitter;
    const ProjectSettings& settings = project.GetSettings();
    emitter << settings.projectName;
    emitter << settings.projectPath.string();
    emitter << settings.projectAssetPath.string();

    FileSystem::CreateFolder(path, settings.projectName);
    path /= settings.projectName;

    FileSystem::SyncWriteAtPathAsString(path / "Project.proj", emitter.c_str());
}

void ProjectSerializer::Deserialize(const Project& project, Path path)
{
}

}
