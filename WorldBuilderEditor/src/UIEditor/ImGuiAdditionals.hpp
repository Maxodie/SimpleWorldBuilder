#pragma once
#include "Core/Core.hpp"

namespace WB
{
class WB_ImGui
{
public:
    WB_ImGui() = delete;
    ~WB_ImGui() = delete;

    static bool BeginBottomMainMenuBar(float height);
    static void EndBottomMainMenuBar();

    static void  TextCentered(const std::string& text);
    static void  TextCentered(const std::string& text, float maxRegionSizeX);
};

}
