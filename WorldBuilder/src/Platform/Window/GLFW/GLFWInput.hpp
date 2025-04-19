#pragma once

#include "Core/Input/Input.hpp"
#include "Core/Window/Window.hpp"
#include <GLFW/glfw3.h>

namespace WB
{

class GLFWInput : public Input
{
public:
    GLFWInput() = default;
    virtual void BindWindow(const SharedPtr<Window> window) override;

protected:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

}
