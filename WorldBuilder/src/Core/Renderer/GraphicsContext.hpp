#pragma once
#include "Core/Core.hpp"

namespace WB
{

class GraphicsContext
{
public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;
    virtual void InitGraphicsContext() = 0;
    virtual void ShutdownGraphicsContext() = 0;

    static UniquePtr<GraphicsContext> CreateContext();
};

}
