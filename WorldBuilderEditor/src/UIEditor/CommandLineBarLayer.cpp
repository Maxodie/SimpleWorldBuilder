#include "UIEditor/CommandLineBarLayer.hpp"
#include "UIEditor/ImGuiAdditionals.hpp"

#include "WorldBuilder.hpp"
#include "Core/Editor/ImGuiLayer.hpp"

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
    CORE_LOG_SUCCESS("ImGUI Command line bar Layer detached");
}

void CommandLineBarLayer::OnInputCallback(Keycode key)
{
    inputs += static_cast<char>(key);
}

}
