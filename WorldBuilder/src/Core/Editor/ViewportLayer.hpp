#pragma once

#include "Core/Commons/Camera.hpp"
#include "Core/LayerStack.hpp"
#include "Core/Renderer/FrameBuffer.hpp"

namespace WB
{

class ViewportLayer : public Layer
{
public:
    ViewportLayer(Camera& cam, SharedPtr<FrameBuffer> frameBuffer);
    ~ViewportLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

private:
    float m_maxFov = 180;

    Camera& m_cam;
    SharedPtr<WB::FrameBuffer> m_frameBuffer;
    glm::vec2 m_viewportSize;
};

}

