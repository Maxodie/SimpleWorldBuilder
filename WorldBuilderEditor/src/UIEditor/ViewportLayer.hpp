#pragma once

#include "WorldBuilder.hpp"

namespace WB
{

class ViewportLayer : public Layer
{
public:
    ViewportLayer(Scene3D& scene);
    ViewportLayer() = delete;
    virtual ~ViewportLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    WB_INLINE void Bind() { m_frameBuffer->Bind(); }
    WB_INLINE void Unbind() { m_frameBuffer->Unbind(); }

private:
    float m_maxFov = 180;

    SharedPtr<WB::FrameBuffer> m_frameBuffer;
    glm::vec2 m_viewportSize;

    Scene3D& m_scene;
};

}

