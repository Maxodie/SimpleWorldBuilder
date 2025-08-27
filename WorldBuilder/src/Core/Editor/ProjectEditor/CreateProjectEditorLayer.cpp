#include "Core/Editor/ProjectEditor/CreateProjectEditorLayer.hpp"
#include "Core/Application.hpp"
#include "Core/Project.hpp"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

namespace WB
{

CreateProjectEditorLayer::CreateProjectEditorLayer()
    : Layer()
{
}

CreateProjectEditorLayer::~CreateProjectEditorLayer()
{

}

void CreateProjectEditorLayer::Update()
{

}

void CreateProjectEditorLayer::UpdateGUI()
{
    ImGui::OpenPopup("new_project_popup", ImGuiPopupFlags_MouseButtonRight);

    if (ImGui::BeginPopup("new_project_popup"))
    {
        ImGui::Text("Create a new project");

        ImGui::Text("Path");
        ImGui::SameLine();
        ImGui::InputText("##Path", &pathBuffer);

        ImGui::Text("Name");
        ImGui::SameLine();
        ImGui::InputText("##Name", &nameBuffer);

        if (ImGui::Button("Create"))
        {
            SharedPtr<Project> project = Project::CreateProject(pathBuffer, nameBuffer);
            if (project)
            {
                Project::SetActiveProject(project);
            }

            Close();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            Close();
        }

        ImGui::EndPopup();
    }
}

void CreateProjectEditorLayer::OnAttach()
{
    CORE_LOG_SUCCESS("Create project editor attached");
}

void CreateProjectEditorLayer::OnDetach()
{
    CORE_LOG_SUCCESS("Create project editor detached");
}

void CreateProjectEditorLayer::Close()
{
    ImGui::CloseCurrentPopup();
    GetContext()->RemoveLayer<CreateProjectEditorLayer>();
}

}
