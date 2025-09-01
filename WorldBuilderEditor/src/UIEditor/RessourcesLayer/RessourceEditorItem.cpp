#include "UIEditor/RessourcesLayer/RessourceEditorItem.hpp"
#include "UIEditor/RessourcesLayer/RessourcesLayer.hpp"

#include "WorldBuilder.hpp"
#include "imgui.h"

namespace WB
{

RessourceEditorItem::RessourceEditorItem(WeakPtr<AssetMetaData>& metaData)
    : m_metaData(metaData)
{

}

void RessourceEditorItem::Draw()
{
    if(!m_metaData.lock())
    {
        return;
    }

    static bool selected = false;

    if(ImGui::Selectable(m_metaData.lock()->path.string().c_str(), selected))
    {
        if (ImGui::IsKeyDown(ImGuiKey_Enter))
        {
            Open();
        }
    }

    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        Open();
    }

}


//file
RessourceEditorFile::RessourceEditorFile(WeakPtr<AssetMetaData>& metaData)
    : RessourceEditorItem(metaData)
{

}

void RessourceEditorFile::Open()
{
}

//folder
RessourceEditorFolder::RessourceEditorFolder(WeakPtr<AssetMetaData>& metaData, RessourcesLayer& context)
    : RessourceEditorItem(metaData), m_context(context)
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

}
