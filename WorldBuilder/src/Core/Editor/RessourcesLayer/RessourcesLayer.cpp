#include "Core/Editor/RessourcesLayer/RessourcesLayer.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"
#include "imgui.h"

namespace WB
{

RessourcesLayer::RessourcesLayer()
{
    m_currentViewPath = Project::GetActive()->GetSettings().projectAssetPath;
}

void RessourcesLayer::Update()
{

}

void RessourcesLayer::UpdateGUI()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Ressources");
    ImVec2 ressourcesPanelSize = ImGui::GetContentRegionAvail();

    if(ImGui::Button("Reload"))
    {
        AssetMetaData metaData;
        Path metaPath;
        for(const auto& entry : DirectoryIterator(m_currentViewPath))
        {
            metaPath = entry.path() / EditorAssetManager::metaExtention;
            if(FileSystem::HasExtension(entry.path(), EditorAssetManager::metaExtention))
            {
                if(ProjectSerializer::Deserialize(metaData, entry.path()))
                {
                    //create selectable items;
                }
            }
            else if(!FileSystem::Exists(metaPath))
            {
                metaData.path = entry.path();
                ProjectSerializer::Serialize(metaData, metaPath);
            }
        }
        for(const auto& entry : DirectoryIterator(m_currentViewPath))
        {
            FileSystem::GetEngineDefaultRessourcesPath();
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void RessourcesLayer::OnAttach()
{
    CORE_LOG_SUCCESS("Ressources layer editor attached");
}

void RessourcesLayer::OnDetach()
{
    CORE_LOG_SUCCESS("Ressources layer editor detached");
}


}
