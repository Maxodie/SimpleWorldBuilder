#pragma once
#include "Core/Event/WindowEvent.hpp"
#include "Core/LayerStack.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Window/Window.hpp"
#include "Core/Input/Input.hpp"

namespace WB
{

class Application : public EventDispatcher
{
public:
    ~Application() = default;

    void Start();
    void Run();
    void HandleEvents();
    void HandleSwapBuffers();
    void Close();
    void Shutdown();

    void OnEvent(Event& event);
    void OnApplicationCloseEvent(const WindowCloseEvent& event);
    void OnApplicationResizeEvent(const WindowResizeEvent& event);

    WB_INLINE const SharedPtr<Window>& GetMainWindow() const
    {
        return m_windows[m_mainWindowID];
    }

    void CreateWindow(const Window::WindowCreateData& windowData = Window::WindowCreateData(), bool isMainWindow = false);

    template<typename TLayer, typename... TArgs>
    WB_INLINE void AddLayer(TArgs&&... args)
    {
        m_layerStack.AddLayer<TLayer>(std::forward<TArgs>(args)...);
    }

    template<typename TLayer>
    WB_INLINE void RemoveLayer()
    {
        PostTask(WB_BIND_FUN0(m_layerStack.RemoveLayer<TLayer>()));
    }

    static WB_INLINE const constexpr Application& Get()
    {
        if(!s_instance)
        {
            Create();
        }

        return *s_instance;
    }

    static WB_INLINE Application& Create()
    {
        s_instance = new Application();
        CORE_LOG_SUCCESS("App created");
        return *s_instance;
    }

protected:
    Application();

private:
    static Application* s_instance;

    SharedPtr<Input> m_input;
    LayerStack m_layerStack;
    std::vector<SharedPtr<Window>> m_windows;
    int32_t m_mainWindowID = -1;
    bool m_isRunning;
    bool m_isMinimized;
};

}
