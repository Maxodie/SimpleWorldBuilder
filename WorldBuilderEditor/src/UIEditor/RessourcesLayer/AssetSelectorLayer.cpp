#include "Core/Log/Log.hpp"
#include "WorldBuilder.hpp"
#include "Core/AssetManager/EditorAssetManager.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
#include "imgui.h"

namespace WB
{
AssetSelectorLayer::AssetSelectorLayer(AssetType type)
    : m_type(type)
{
}

void AssetSelectorLayer::Update()
{

}

void AssetSelectorLayer::UpdateGUI()
{
    ImGui::OpenPopup("open_asset_selector", ImGuiPopupFlags_MouseButtonRight);

    ImVec2 min = ImGui::GetMousePosOnOpeningCurrentPopup();
    ImVec2 max;
    max.x = min.x + ImGui::GetContentRegionAvail().x;
    max.y  = min.y + ImGui::GetContentRegionAvail().y;

    if(!ImGui::IsMouseHoveringRect(min, max) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        GetContext()->RemoveLayer<AssetSelectorLayer>();
    }

    if (ImGui::BeginPopup("open_asset_selector"))
    {

        ImGui::Text("open asset selector");

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
        if(ImGui::BeginChild("open_asset_selector_child", ImVec2(550, 200), ImGuiChildFlags_None, window_flags))
        {
            if(ImGui::Button("Close"))
            {
                GetContext()->RemoveLayer<AssetSelectorLayer>();
            }

            MetaDataRegistry& registry = Project::GetActive()->GetEditorAssetManager()->GetMetaDataRegistry();
            for(auto& [key, metaData] : registry)
            {
                if(metaData->type == AssetType::MODEL)
                {
                    if(ImGui::Selectable(metaData->name.c_str()))
                    {
                        if (ImGui::IsKeyDown(ImGuiKey_Enter))
                        {
                            GetContext()->RemoveLayer<AssetSelectorLayer>();
                            m_selectionCallback(key);
                        }
                    }

                    if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        GetContext()->RemoveLayer<AssetSelectorLayer>();
                        m_selectionCallback(key);
                    }
                }
            }
            ImGui::EndChild();
        }

        ImGui::EndPopup();
    }
}

void AssetSelectorLayer::OnAttach()
{

}

void AssetSelectorLayer::OnDetach()
{

}

}
