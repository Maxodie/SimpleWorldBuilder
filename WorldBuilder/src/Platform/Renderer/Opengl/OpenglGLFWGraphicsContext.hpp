#pragma once
#include "Core/Renderer/GraphicsContext.hpp"

namespace WB
{

class OpenglGLFWGraphicsContext : public GraphicsContext
{
    virtual void InitGraphicsContext() override;
    virtual void ShutdownGraphicsContext() override;
};

}
