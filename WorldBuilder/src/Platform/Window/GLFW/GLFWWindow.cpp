#include "Platform/Window/GLFW/GLFWWindow.hpp"
#include "Core/Event/WindowEvent.hpp"
#include "Core/Core.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace WB
{

WB_GLFWWindow::WB_GLFWWindow(const WindowCreateData& windowData)
    : Window({.name = windowData.name, .w = windowData.w, .h = windowData.h})
{
    Init(windowData);
}

void WB_GLFWWindow::Init(const WindowCreateData& windowData)
{
    if(!glfwInit())
    {
        WB_CORE_ASSERT(false, "cannot init glfw");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    m_graphicsContext = GraphicsContext::CreateContext();//need to create the context before calling glfwCreateWindow

    m_window = glfwCreateWindow(windowData.w, windowData.h, windowData.name.c_str(), nullptr, nullptr);
    m_native = m_window;
    if(!m_window)
    {
        WB_CORE_ASSERT(false, "cannot create window");
    }

    glfwMakeContextCurrent(m_window);

    m_graphicsContext->InitGraphicsContext();

    glfwSetWindowUserPointer(m_window, this);

    glfwSetErrorCallback([](int error, const char* description) {
        CORE_LOG_ERROR("GLFW error code : %d, %s", error, description);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
        WB_GLFWWindow* appWindow = static_cast<WB_GLFWWindow*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        appWindow->PostEvent<WindowCloseEvent>(event);
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        WB_GLFWWindow* appWindow = static_cast<WB_GLFWWindow*>(glfwGetWindowUserPointer(window));
        WindowResizeEvent event{static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
        appWindow->PostEvent<WindowResizeEvent>(event);
        appWindow->PollEvent();
    });
}

void WB_GLFWWindow::PollWindowEvents()
{
    glfwPollEvents();
    Window::PollWindowEvents();
}

void WB_GLFWWindow::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void WB_GLFWWindow::Shutdown()
{
    glfwTerminate();
}

}
