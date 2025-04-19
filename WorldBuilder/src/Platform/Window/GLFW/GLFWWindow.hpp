#pragma once
#include "Core/Window/Window.hpp"
#include "Core/Renderer/GraphicsContext.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace WB
{

class WB_GLFWWindow : public Window
{
public:
    WB_GLFWWindow(const WindowCreateData& windowData);
    virtual ~WB_GLFWWindow() = default;

    void Init(const WindowCreateData& windowData) override;
    void Shutdown() override;
    void PollWindowEvents() override;
    void SwapBuffers() override;

private:
    GLFWwindow* m_window;
    UniquePtr<GraphicsContext> m_graphicsContext;
};

}
