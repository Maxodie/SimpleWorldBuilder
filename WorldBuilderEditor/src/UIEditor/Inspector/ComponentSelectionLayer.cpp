#include "UIEditor/Inspector/ComponentSelectionLayer.hpp"
#include "imgui.h"

namespace WB
{

ComponentSelectorLayer::ComponentSelectorLayer()
{
}

void ComponentSelectorLayer::Update()
{

}

void ComponentSelectorLayer::UpdateGUI()
{
    ImGui::OpenPopup("open_component_selector", ImGuiPopupFlags_MouseButtonRight);

    ImVec2 min = ImGui::GetMousePosOnOpeningCurrentPopup();
    ImVec2 max;
    max.x = min.x + ImGui::GetContentRegionAvail().x;
    max.y  = min.y + ImGui::GetContentRegionAvail().y;

    if(!ImGui::IsMouseHoveringRect(min, max) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        GetContext()->RemoveLayer<ComponentSelectorLayer>();
    }

    if (ImGui::BeginPopup("open_component_selector"))
    {

        ImGui::Text("open component selector");

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
        if(ImGui::BeginChild("open_component_selector_child", ImVec2(550, 200), ImGuiChildFlags_None, window_flags))
        {
            if(ImGui::Button("Close"))
            {
                GetContext()->RemoveLayer<ComponentSelectorLayer>();
            }

            for(auto typeID : m_componentsID)
            {
                if(ImGui::Selectable(typeID.name()))
                {
                    if (ImGui::IsKeyDown(ImGuiKey_Enter))
                    {
                        GetContext()->RemoveLayer<ComponentSelectorLayer>();
                        m_selectionCallback(typeID);
                    }
                }

                if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    GetContext()->RemoveLayer<ComponentSelectorLayer>();
                    m_selectionCallback(typeID);
                }
            }

            ImGui::EndChild();
        }

        ImGui::EndPopup();
    }
}

void ComponentSelectorLayer::OnAttach()
{

}

void ComponentSelectorLayer::OnDetach()
{

}

}
