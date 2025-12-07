#include "UIEditor/GuizmoEditor.hpp"
#include "Core/Log/Log.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"
#include "ImGuizmo.h"

void GuizmoEditor::Update(WB::Scene3D& context)
{
    if(s_selectedEntity.Exists())
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        WB::Entity cameraEntity = context.GetMainCameraEntity();
        const auto& cameraComp = cameraEntity.Get<WB::Camera>();
        const glm::mat4& camProjection = cameraComp.GetProjectionMatrix();
        // const glm::mat4& camView = cameraEntity.Get<WB::TransformComponent>().GetModelMatrix();
        const glm::mat4& camView = cameraComp.GetViewMatrix();

        if(s_selectedEntity.Has<WB::TransformComponent>())
        {
            auto& tc = s_selectedEntity.Get<WB::TransformComponent>();
            glm::mat4 entityTr = tc.GetModelMatrix();

            // glm::mat4 gridTr{1};
            // gridTr = glm::translate(gridTr, glm::vec3(0, -0.1, 0));
            // ImGuizmo::DrawGrid(glm::value_ptr(camView), glm::value_ptr(camProjection), glm::value_ptr(gridTr), 2);

            ImGuizmo::Manipulate(glm::value_ptr(camView), glm::value_ptr(camProjection),
                                 static_cast<ImGuizmo::OPERATION>(s_guizmoType), static_cast<ImGuizmo::MODE>(s_guizmoSpace), glm::value_ptr(entityTr));

            if(ImGuizmo::IsUsing())
            {
                glm::vec3 translate, rotation, scale;
                ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(entityTr), glm::value_ptr(translate), glm::value_ptr(rotation), glm::value_ptr(scale));
                tc.SetPosition(translate);
                tc.SetRotation(glm::radians(tc.GetRotation() + rotation - tc.GetRotation()));
                tc.SetScale(scale);
            }
        }

    }
}

void GuizmoEditor::OnEntitySelectedInHierarchy(WB::Entity& entity)
{
    s_selectedEntity = entity;
}

void GuizmoEditor::SetGuizmoType(Type type)
{
    s_guizmoType = type;
}

void GuizmoEditor::SetGuizmoSpace(Space space)
{
    s_guizmoSpace = space;
}
