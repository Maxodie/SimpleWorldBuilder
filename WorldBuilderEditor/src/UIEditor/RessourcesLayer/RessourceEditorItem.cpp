#include "UIEditor/RessourcesLayer/RessourceEditorItem.hpp"
#include "Core/AssetManager/Engine/EngineAssetManager.hpp"
#include "Core/Log/Log.hpp"
#include "Editor.hpp"
#include "UIEditor/ImGuiAdditionals.hpp"
#include "UIEditor/RessourcesLayer/RessourcesLayer.hpp"

#include "WorldBuilder.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace WB
{

RessourceEditorItem::RessourceEditorItem(WeakPtr<AssetMetaData> metaData, RessourcesLayer& context)
    : m_context(context), m_metaData(metaData)
{
    if(!m_metaData.lock())
    {
        CORE_LOG_ERROR("Item file does not exist");
    }

    if(m_metaData.lock())
    {
        switch (m_metaData.lock()->type)
        {
            case AssetType::UNKNOWN:
                {

                }
            case AssetType::FOLDER:
                {
                    m_icon = EngineAssetManager::Get().GetAsset("file_icon");
                    break;
                }
            case AssetType::SHADER:
                {
                    m_icon = EngineAssetManager::Get().GetAsset("file_icon");
                    break;
                }
            case AssetType::MODEL:
                {
                    m_icon = EngineAssetManager::Get().GetAsset("file_icon");
                    break;
                }
            case AssetType::MATERIAL:
                {
                    m_icon = EngineAssetManager::Get().GetAsset("file_icon");
                    break;
                }
            case AssetType::TEXTURE2D:
                {
                    m_icon = Project::GetActive()->GetAssetManager()->GetAsset<Texture2D>(m_metaData.lock()->id);
                    m_uv0 = {1, 1};
                    m_uv1 = {0, 0};
                    break;
                }
            case AssetType::SCENE:
                {
                    m_icon = EngineAssetManager::Get().GetAsset("file_icon");
                    break;
                }

            default:
                {
                    m_icon = EngineAssetManager::Get().GetAsset("file_icon");
                    break;
                }
        }
    }

    WB_CORE_ASSERT(m_icon.lock(), "Item file icon does not exist");
}

void RessourceEditorItem::Draw()
{
    if(!m_metaData.lock())
    {
        return;
    }

    if(m_icon.lock())
    {
        std::string name = FileSystem::GetFileName(m_metaData.lock()->path);

        ImGui::BeginGroup();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));

        if(ImGui::ImageButton(("##RessourceItem" + name).c_str(),
                              m_icon.lock()->GetTextureID(), m_itemSize, m_uv0, m_uv1))
        {
            WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(m_metaData.lock()->id);
            if(metaData.lock())
            {
                m_context.OnAssetSelectedCallback(metaData.lock());
            }

            if (ImGui::IsKeyDown(ImGuiKey_Enter))
            {
                Open();
            }

        }

        WB_ImGui::TextCentered(name.c_str(), m_itemSize.x);
        ImGui::EndGroup();
        ImGui::PopStyleColor();
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            Open();
        }
    }
}


//file
RessourceEditorFile::RessourceEditorFile(WeakPtr<AssetMetaData> metaData, RessourcesLayer& context)
    : RessourceEditorItem(metaData, context)
{

}

void RessourceEditorFile::Open()
{
}

//folder
RessourceEditorFolder::RessourceEditorFolder(WeakPtr<AssetMetaData> metaData, RessourcesLayer& context)
    : RessourceEditorItem(metaData, context)
{

}

void RessourceEditorFolder::Open()
{
    if(!m_metaData.lock())
    {
        CORE_LOG_ERROR("could not switch folder, metaData doe not exist anymore");
        return;
    }

    m_context.ChangeDirectory(m_metaData.lock()->path);
}

//scene
RessourceEditorScene::RessourceEditorScene(WeakPtr<class AssetMetaData> metaData, RessourcesLayer& context)
    : RessourceEditorItem(metaData, context)
{

}

void RessourceEditorScene::Open()
{
    if(!m_metaData.lock())
    {
        CORE_LOG_ERROR("could not open scene, metaData doe not exist anymore");
        return;
    }

    WeakPtr<EditorLayer> editorLayer = m_context.GetContext()->GetLayer<EditorLayer>();
    if(!editorLayer.lock())
    {
        return;
    }

    editorLayer.lock()->SwitchScene(m_metaData.lock()->id);
}

}
