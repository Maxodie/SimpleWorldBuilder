#pragma once

#include "WorldBuilder.hpp"

namespace WB
{

class ViewportLayer : public Layer
{
public:
    ViewportLayer(Camera& cam, SharedPtr<FrameBuffer> frameBuffer);
    virtual ~ViewportLayer();

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

