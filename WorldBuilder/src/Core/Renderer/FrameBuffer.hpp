#pragma once
#include "Core/Core.hpp"

namespace WB
{

class FrameBuffer
{
public:
    virtual ~FrameBuffer() = default;

    virtual void Invalidate() = 0;
    virtual void Resize(uint32_t width, uint32_t height) = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static SharedPtr<FrameBuffer> Create();
};

}
