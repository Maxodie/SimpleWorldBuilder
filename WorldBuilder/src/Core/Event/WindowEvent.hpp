#pragma once
#include "Core/Event/Event.hpp"

namespace WB
{

struct WindowCloseEvent : Event
{
public:
    WindowCloseEvent() = default;
};

struct WindowResizeEvent : Event
{
public:
    WindowResizeEvent(uint32_t width, uint32_t height)
        : Width(width), Height(height)
    {

    }

    uint32_t Width;
    uint32_t Height;
};

}
