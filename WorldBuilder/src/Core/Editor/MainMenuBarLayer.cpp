#include "Core/Editor/MainMenuBarLayer.hpp"
#include "Core/Project.hpp"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "regex"

namespace WB
{

MainMenuBarLayer::MainMenuBarLayer() : Layer()
{
}

MainMenuBarLayer::~MainMenuBarLayer()
{
}

void MainMenuBarLayer::Update()
{

}

void MainMenuBarLayer::UpdateGUI()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New Project"))
            {
                m_isNewFolderDialogOpen = true;
            }

            if(ImGui::MenuItem("Open Project"))
            {
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }


    if(m_isNewFolderDialogOpen)
    {
        ImGui::OpenPopup("new_project_popup", ImGuiPopupFlags_MouseButtonRight);
    }
    //create new project popup
    if(ImGui::BeginPopup("new_project_popup"))
    {
        ImGui::Text("Create a new project");

        ImGui::Text("Path");
        ImGui::SameLine();
        ImGui::InputText("##Path", &pathBuffer);

        ImGui::Text("Name");
        ImGui::SameLine();
        ImGui::InputText("##Name", &nameBuffer);

        if(ImGui::Button("Create"))
        {
            std::string pathName = nameBuffer;
            std::regex const filter("[^0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-]");
            pathName = std::regex_replace(pathName, filter, "");
            Path folderPath = pathBuffer;
            FileSystem::CreateFolder(folderPath, pathName);
            SharedPtr<Project> project = Project::CreateProject(folderPath / pathName, nameBuffer);
            if(project)
            {
                Project::SetActiveProject(project);
            }

            std::string pathBuffer{"C:/"};
            std::string nameBuffer{"New Project"};
            ImGui::CloseCurrentPopup();
            m_isNewFolderDialogOpen = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel"))
        {
            std::string pathBuffer{"C:/"};
            std::string nameBuffer{"New Project"};
            ImGui::CloseCurrentPopup();
            m_isNewFolderDialogOpen = false;
        }

        ImGui::EndPopup();
    }
    //
}

void MainMenuBarLayer::OnAttach()
{
    CORE_LOG_SUCCESS("ImGUI Main menu bar Layer attached");
}

void MainMenuBarLayer::OnDetach()
{
    CORE_LOG_SUCCESS("ImGUI Main menu bar Layer detached");
}

}
