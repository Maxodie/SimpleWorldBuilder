#include "Core/Window/Window.hpp"
#include "Platform/Window/GLFW/GLFWWindow.hpp"
#include "Core/Core.hpp"

namespace WB
{

Window::API Window::s_api = Window::API::GLFW;

Window::Window(WindowData&& windowData)
    : m_windowData(std::move(windowData))
{
}

UniquePtr<Window> Window::CreateWindow(const WindowCreateData& windowData)
{
    switch (GetAPI())
    {
        case Window::API::GLFW:
            CORE_LOG_SUCCESS("Window API creation...");
            return MakeUnique<WB_GLFWWindow>(windowData);
        break;

        case Window::API::None:
            CORE_LOG_ERROR("Unknown Window API : %d", GetAPI());
        break;

        default:
            CORE_LOG_ERROR("Unknown Window API : %d", GetAPI());
        break;
    }

    CORE_LOG_ERROR("Unknown Window API : %d", GetAPI());
    return nullptr;
}

void Window::PollWindowEvents()
{
    PollEvent();
}

}
