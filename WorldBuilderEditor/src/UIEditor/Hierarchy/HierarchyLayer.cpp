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

    if(!m_scene.lock())
    {
        ImGui::End();
        ImGui::PopStyleVar();
        return;
    }

    if(ImGui::Button("Create Entity"))
    {
        Entity entity = m_scene.lock()->CreateEntity();
        entity.AddComponent<InfoComponent>(entity.GetHandle());
    }

    if(ImGui::BeginChild("Entity Hierarchy"))
    {
        m_scene.lock()->EntityView<InfoComponent>(
            [&](auto entity, InfoComponent& info)
            {
                if(ImGui::Selectable((info.name + "##" + static_cast<char>(info.handle)).c_str()))
                {
                    m_onEntitySelectedCallback(std::move(Entity(*m_scene.lock(), entity)));
                }
            });

        ImGui::EndChild();
    }

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
