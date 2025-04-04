#pragma once
#include "Core/Core.hpp"
#include "Core/Event/Event.hpp"

namespace WB
{

class Window : public EventDispatcher
{
public:
    enum class API
    {
        None,
        GLFW
    };

    struct WindowCreateData
    {
        std::string name = "default window";
        uint32_t w = 640, h = 800;
    };

    struct WindowData
    {
        std::string name = "default window";
        uint32_t w = 640, h = 800;
    };


public:
    Window(WindowData&& windowData);
    virtual ~Window() = default;

    virtual void Init(const WindowCreateData& windowData) = 0;
    virtual void Shutdown() = 0;
    virtual void PollWindowEvents();
    virtual void SwapBuffers() = 0;

    static UniquePtr<Window> CreateWindow(const WindowCreateData& windowData);

    inline static API GetAPI() { return s_api; }

private:
    static API s_api;
    WindowData m_windowData;
};

}
