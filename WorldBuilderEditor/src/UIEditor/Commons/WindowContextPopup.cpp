#include "UIEditor/Commons/WindowContextPopup.hpp"
#include "imgui.h"

namespace WB
{

const float WindowContextPopup::s_buttonHeight = 30.f;

WindowContextPopup::WindowContextPopup()
{

}

void WindowContextPopup::Begin()
{
    ImVec2 HierarchySize = ImGui::GetWindowSize();
    ImVec2 HierarchyPos = ImGui::GetWindowPos();

    if(ImGui::IsMouseHoveringRect(HierarchyPos, {HierarchyPos.x + HierarchySize.x, HierarchyPos.y + HierarchySize.y}))
    {
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            ImGui::OpenPopup("right_click_context_menu", ImGuiPopupFlags_MouseButtonRight);
        }
    }

    if(ImGui::BeginPopup("right_click_context_menu"))
    {
        if(ImGui::BeginChild("right click child", ImVec2(150.f, m_registry.size() * s_buttonHeight)))
        {
            for(const auto& [key, value] : m_registry)
            {
                if(ImGui::Button(key.c_str(), ImVec2(150.f, s_buttonHeight)))
                {
                    value();
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndChild();
        }
        ImGui::EndPopup();
    }
}

void WindowContextPopup::End()
{

}

void WindowContextPopup::AddElement(const std::string& name, WindowContextPopupCallback&& callback)
{
    if(m_registry.find(name) == m_registry.end())
    {
        m_registry[name] = std::move(callback);
    }
}

}
