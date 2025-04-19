#pragma once
#include "Core/Renderer/FrameBuffer.hpp"

namespace WB
{

class OpenglFrameBuffer : public FrameBuffer
{
public:
    struct Info
    {
        uint32_t width = 800;
        uint32_t height = 640;
    };

public:
    OpenglFrameBuffer();
    virtual ~OpenglFrameBuffer();

    virtual void Invalidate() override;
    virtual void Resize(uint32_t width, uint32_t height) override;
    virtual void Bind() override;
    virtual void Unbind() override;

private:
    void TryDestroyFrameBuffer();

private:
    uint32_t m_frameBuffer;
    uint32_t m_renderBuffer;
    uint32_t m_frameBufferTextureColor;
    uint32_t m_frameBufferTextureDepth;
    Info m_info;
};


}
