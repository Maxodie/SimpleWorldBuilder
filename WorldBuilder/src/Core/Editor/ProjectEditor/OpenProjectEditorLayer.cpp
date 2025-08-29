#include "Core/Editor/ProjectEditor/OpenProjectEditorLayer.hpp"
#include "Core/Application.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"

#include "Core/Serializer/ProjectSerializer.hpp"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

namespace WB
{

OpenProjectEditorLayer::OpenProjectEditorLayer(bool canCancel)
    : Layer(), m_projectList(Project::GetProjectList()), m_canCancel(canCancel)
{
}

OpenProjectEditorLayer::~OpenProjectEditorLayer()
{
}

void OpenProjectEditorLayer::Update()
{

}

void OpenProjectEditorLayer::UpdateGUI()
{
    ImGui::OpenPopup("open_project_popup", ImGuiPopupFlags_MouseButtonRight);

    if (ImGui::BeginPopup("open_project_popup"))
    {
        ImGui::Text("Open a project");

        ImVec2 windowPos = ImGui::GetContentRegionAvail();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
        ImGui::BeginChild("ChildL", ImVec2(550, 200), ImGuiChildFlags_None, window_flags);

        for(int i = 0; i < m_projectList.paths.size(); i++)
        {
            if (ImGui::Button(("Open " + m_projectList.names[i]).c_str()))
            {
                if(!Project::OpenProject(m_projectList.paths[i]))
                {
                    CORE_LOG_ERROR("failed to open project path : %s", m_projectList.paths[i].string().c_str());
                }

                for(const auto& callback : m_projectOpenedCallbacks)
                {
                    callback();
                }

                Close();
            }

        }
        ImGui::EndChild();

        ImGui::Text("Path");
        ImGui::SameLine();
        ImGui::InputText("##Path", &pathBuffer);

        if (ImGui::Button("Open existing project"))
        {
            Path fullpath = pathBuffer;
            ProjectSettings settings;
            if(ProjectSerializer::Deserialize(settings, fullpath))
            {
                SharedPtr<Project> project = MakeShared<Project>(settings);
                Project::AddProjectToProjectList(project);
            }
            else
            {
                CORE_LOG_ERROR("failed to open project path : %s", fullpath.string().c_str());
            }
        }

        if(m_canCancel)
        {
            if (ImGui::Button("Cancel"))
            {
                Close();
            }
        }

        ImGui::EndPopup();
    }
}

void OpenProjectEditorLayer::OnAttach()
{
    CORE_LOG_SUCCESS("Open project editor attached");
}

void OpenProjectEditorLayer::OnDetach()
{
    CORE_LOG_SUCCESS("Open project editor detached");
}

void OpenProjectEditorLayer::AddOnProjectOpenedCallback(const ProjectOpenedCallback&& fun)
{
    m_projectOpenedCallbacks.emplace_back(std::move(fun));
}

void OpenProjectEditorLayer::Close()
{
    ImGui::CloseCurrentPopup();
    GetContext()->RemoveLayer<OpenProjectEditorLayer>();
}

}
