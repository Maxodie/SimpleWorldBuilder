#include "UIEditor/RessourcesLayer/RessourcesLayer.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Serializer/SceneSerializer.hpp"
#include "UIEditor/RessourcesLayer/RessourceEditorItem.hpp"
#include "WorldBuilder.hpp"
#include "Editor.hpp"

#include "Core/Utils/FileSystem.hpp"
#include "imgui.h"

namespace WB
{

RessourcesLayer::RessourcesLayer()
{
    m_currentViewPath = Project::GetActive()->GetSettings().projectAssetPath;

    //create scene
    m_contextPopup.AddElement(
        "Create Scene",
        [&]()
        {
            WeakPtr<Scene3D> scene = Project::GetActive()->GetEditorAssetManager()->CreateAsset<Scene3D>(AssetType::SCENE, m_currentViewPath, "new Scene");
            if(scene.lock())
            {
                WeakPtr<EditorLayer> editorLayer = GetContext()->GetLayer<EditorLayer>();
                if(!editorLayer.lock())
                {
                    return;
                }
            }
        }
    );

    m_contextPopup.AddElement(
        "Create Material",
        [&]()
        {
            WeakPtr<Material> material = Project::GetActive()->GetEditorAssetManager()->CreateAsset<Material>(AssetType::MATERIAL, m_currentViewPath, "new Material");
            if(material.lock())
            {
                WeakPtr<EditorLayer> editorLayer = GetContext()->GetLayer<EditorLayer>();
                if(!editorLayer.lock())
                {
                    return;
                }
            }
        }
    );
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

    float windowVisibleX2 = ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x;
    ImGuiStyle& style = ImGui::GetStyle();
    for(uint32_t i = 0; i < m_items.size(); ++i)
    {
        m_items[i]->Draw();
        float lastItemX2 = ImGui::GetItemRectMax().x;
        float nextItemX2 = lastItemX2 + style.ItemSpacing.x + m_items[i]->GetSize().x; // Expected position if next button was on same line
        if (i + 1 < m_items.size() && nextItemX2 < windowVisibleX2)
        {
            ImGui::SameLine();
        }
    }

    m_contextPopup.Begin();
    m_contextPopup.End();

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

    if(metaData.lock()->type == AssetType::FOLDER)
    {
        m_items.emplace_back(MakeShared<RessourceEditorFolder>(metaData, *this));
    }
    else if(metaData.lock()->type == AssetType::SCENE)
    {
        m_items.emplace_back(MakeShared<RessourceEditorScene>(metaData, *this));
    }
    else
    {
        m_items.emplace_back(MakeShared<RessourceEditorFile>(metaData, *this));
    }
}


}
