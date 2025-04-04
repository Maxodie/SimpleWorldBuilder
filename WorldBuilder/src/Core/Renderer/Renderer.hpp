#pragma once
#include "Core/Core.hpp"
#include "Core/Renderer/RenderCommand.hpp"

namespace WB
{

class Renderer
{
public:
    static void Init();
    static void Shutdown();

    WB_INLINE static void OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }
};

}
