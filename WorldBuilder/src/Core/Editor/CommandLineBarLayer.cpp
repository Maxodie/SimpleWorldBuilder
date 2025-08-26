#include "Core/Editor/CommandLineBarLayer.hpp"
#include "Core/Editor/ImGuiAdditionals.hpp"
#include "Core/Editor/ImGuiLayer.hpp"
#include "Core/Input/Input.hpp"

#include <imgui.h>

namespace WB
{

CommandLineBarLayer::CommandLineBarLayer() : Layer()
{
    Input::AddAnyInputCallback(WB_BIND_FUN1(WB::CommandLineBarLayer::OnInputCallback));
}

CommandLineBarLayer::~CommandLineBarLayer()
{
}

void CommandLineBarLayer::Update()
{

}

void CommandLineBarLayer::UpdateGUI()
{
    if (WB_ImGui::BeginBottomMainMenuBar(ImGuiLayerBase::MenuBarSize()))
    {
        ImGui::Text(inputs.c_str());
        WB_ImGui::EndBottomMainMenuBar();
    }

}

void CommandLineBarLayer::OnAttach()
{
    CORE_LOG_SUCCESS("ImGUI Command line bar Layer attached");
}

void CommandLineBarLayer::OnDetach()
{
    CORE_LOG_SUCCESS("ImGUI Main menu bar Layer detached");
}

void CommandLineBarLayer::OnInputCallback(Keycode key)
{
    inputs += static_cast<char>(key);
}

}
