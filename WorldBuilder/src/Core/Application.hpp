#pragma once
#include "Core/Event/WindowEvent.hpp"
#include "Core/LayerStack.hpp"
#include "Core/Window/Window.hpp"

namespace WB
{

class Application : public EventDispatcher
{
public:
    Application();
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

    void CreateWindow(const Window::WindowCreateData& windowData = Window::WindowCreateData());

    template<typename TLayer, typename... TArgs>
    void AddLayer(TArgs&&... args)
    {
        m_layerStack.AddLayer<TLayer>(std::forward<TArgs>(args)...);
    }

    template<typename TLayer>
    void RemoveLayer()
    {
        m_layerStack.RemoveLayer<TLayer>();
    }

private:
    bool m_isRunning;
    bool m_isMinimized;
    LayerStack m_layerStack;
    std::vector<UniquePtr<Window>> m_windows;
};

}
