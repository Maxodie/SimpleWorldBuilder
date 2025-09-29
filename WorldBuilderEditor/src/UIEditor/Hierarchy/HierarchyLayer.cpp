#include "UIEditor/Hierarchy/HierarchyLayer.hpp"
#include "WorldBuilder.hpp"

#include "imgui.h"

namespace WB
{
HierarchyLayer::HierarchyLayer(WeakPtr<Scene3D> scene)
    : Layer(), m_scene(scene)
{
    m_windowContextPopup.AddElement("Create Entity",
            [&]()
            {
                Entity entity = m_scene.lock()->CreateEntity();
                entity.AddComponent<InfoComponent>(entity.GetHandle());
            });
}

void HierarchyLayer::Update()
{

}

void HierarchyLayer::UpdateGUI()
{

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Hierarchy");

    if(!m_scene.lock())
    {
        ImGui::Text("No active scene");
        ImGui::End();
        ImGui::PopStyleVar();
        return;
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

        m_windowContextPopup.Begin();
        m_windowContextPopup.End();

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
