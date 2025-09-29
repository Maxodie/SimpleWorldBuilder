#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

using WindowContextPopupCallback = std::function<void()>;

class WindowContextPopup
{
public:
    WindowContextPopup();

    void Begin();
    void End();

    void AddElement(const std::string& name, WindowContextPopupCallback&& callback);

private:
    std::unordered_map<std::string, WindowContextPopupCallback> m_registry;

    static const float s_buttonHeight;
};

}
