#include "UIEditor/RessourcesLayer/RessourcesLayer.hpp"
#include "UIEditor/RessourcesLayer/RessourceEditorItem.hpp"
#include "WorldBuilder.hpp"

#include "Core/Utils/FileSystem.hpp"
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

    if(m_currentViewPath != Project::GetActive()->GetAssetPath())
    {
        if(ImGui::Button("back"))
        {
            m_currentViewPath = m_currentViewPath.parent_path();
        }
    }

    m_items.clear();

    WeakPtr<AssetMetaData> metaData;
    Path metaPath;
    for(const auto& entry : DirectoryIterator(m_currentViewPath))
    {
        metaPath = entry.path();
        metaPath.replace_extension(EditorAssetManager::s_metaExtention);

        if(!FileSystem::Exists(metaPath))
        {
            metaData = Project::GetActive()->GetEditorAssetManager()->CreateMetaData(entry.path());
            if(metaData.lock())
            {
                UpdateFile(metaPath, metaData.lock()->id);
            }
        }
        else
        {
            metaData = Project::GetActive()->GetEditorAssetManager()->LoadMetaData(metaPath);
            if(metaData.lock())
            {
                UpdateFile(metaPath, metaData.lock()->id);
            }
            else
            {
                UpdateFile(metaPath, 0);
            }
        }

    }

    for(auto& item : m_items)
    {
        item->Draw();
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

void RessourcesLayer::ChangeDirectory(const Path& path)
{
    m_currentViewPath = path;
}

void RessourcesLayer::UpdateFile(const Path& metaPath, AssetID assetID)
{
    WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(assetID);
    if(!metaData.lock())
    {
        CORE_LOG_ERROR("could not add ressource item, metaData doe not exist anymore");
        return;
    }

    if(FileSystem::Exists(metaData.lock()->path))
    {
        TryAddItem(assetID);
    }
    else
    {
        FileSystem::Delete(metaPath);
    }
}

void RessourcesLayer::TryAddItem(AssetID assetID)
{
    WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(assetID);
    if(!metaData.lock())
    {
        CORE_LOG_ERROR("could not add ressource item, metaData doe not exist anymore");
        return;
    }

    if(FileSystem::IsFolder(metaData.lock()->path))
    {
        m_items.emplace_back(MakeShared<RessourceEditorFolder>(metaData, *this));
    }
    else
    {
        m_items.emplace_back(MakeShared<RessourceEditorFile>(metaData));
    }
}


}
