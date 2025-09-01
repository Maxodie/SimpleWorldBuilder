#include "UIEditor/ViewportLayer.hpp"
#include "glm/common.hpp"

#include <imgui.h>

namespace WB
{

ViewportLayer::ViewportLayer(Camera& cam, SharedPtr<FrameBuffer> frameBuffer)
    : Layer(), m_cam(cam), m_frameBuffer(frameBuffer)
{
}

ViewportLayer::~ViewportLayer()
{
}

void ViewportLayer::Update()
{

}

void ViewportLayer::UpdateGUI()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Viewport");
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    if (m_viewportSize.x != viewportPanelSize.x || m_viewportSize.y != viewportPanelSize.y)
    {
        m_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        m_frameBuffer->Resize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
        float ratio = fmin(m_viewportSize.x / m_viewportSize.y, m_viewportSize.y / m_viewportSize.x);
        float fov = 80.0f;
        if(ratio < 1.0f && m_viewportSize.x < m_maxFov)
        {
            fov = glm::clamp(m_maxFov - m_viewportSize.x, 80.0f, m_maxFov);
        }
        else if(ratio < 1.0f && m_viewportSize.y < m_maxFov)
        {
            fov = glm::clamp(m_maxFov - m_viewportSize.y, 80.0f, m_maxFov);
        }
        m_cam.ResizeBound(m_viewportSize.x, m_viewportSize.y);
        m_cam.SetFov(fov);
    }
    uint32_t textureID = m_frameBuffer->GetColorAttachmentRendererID();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_viewportSize.x, m_viewportSize.y }, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::PopStyleVar();
    ImGui::End();
}

void ViewportLayer::OnAttach()
{
    CORE_LOG_SUCCESS("ImGUI viewport Layer attached");
}

void ViewportLayer::OnDetach()
{
    CORE_LOG_SUCCESS("ImGUI viewport Layer detached");
}

}
