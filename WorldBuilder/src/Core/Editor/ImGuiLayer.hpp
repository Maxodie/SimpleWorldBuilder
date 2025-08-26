#pragma once

#include "Core/Core.hpp"

namespace WB
{

class ImGuiLayerBase
{
public:
    ImGuiLayerBase() = delete;

    static void BaseInit();
    static void BaseShutdown();

    static void Begin();
    static void End();

    WB_INLINE static float MenuBarSize() { return 25.0f; }

private:
    static bool m_open;
};

}

