#include "UIEditor/Hierarchy/HierarchyLayer.hpp"
#include "WorldBuilder.hpp"

#include "imgui.h"

namespace WB
{

void HierarchyLayer::Update()
{

}

void HierarchyLayer::UpdateGUI()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Hierarchy");
    ImVec2 HierarchyLayer = ImGui::GetContentRegionAvail();

    ImGui::End();
    ImGui::PopStyleVar();
}

void HierarchyLayer::OnAttach()
{

}

void HierarchyLayer::OnDetach()
{

}

}
