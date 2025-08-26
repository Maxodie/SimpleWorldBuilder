#pragma once

namespace WB
{
class WB_ImGui
{
public:
    WB_ImGui() = delete;
    ~WB_ImGui() = delete;

    static bool BeginBottomMainMenuBar(float height);
    static void EndBottomMainMenuBar();
};

}
