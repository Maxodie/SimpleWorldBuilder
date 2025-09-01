#include "UIEditor/MainMenuBarLayer.hpp"
#include "UIEditor/ProjectEditor/CreateProjectEditorLayer.hpp"
#include "UIEditor/ProjectEditor/OpenProjectEditorLayer.hpp"

#include "WorldBuilder.hpp"

#include "imgui.h"

namespace WB
{

MainMenuBarLayer::MainMenuBarLayer()
    : Layer()
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
            if (ImGui::MenuItem("New Project"))
            {
                GetContext()->AddLayer<CreateProjectEditorLayer>();
            }

            if (ImGui::MenuItem("Open Project"))
            {
                GetContext()->AddLayer<OpenProjectEditorLayer>();
            }

          ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void MainMenuBarLayer::OnAttach()
{
    CORE_LOG_SUCCESS("ImGUI Main menu bar Layer attached");
}

void MainMenuBarLayer::OnDetach()
{
    CORE_LOG_SUCCESS("ImGUI Main menu bar Layer detached");
}

} // namespace WB
