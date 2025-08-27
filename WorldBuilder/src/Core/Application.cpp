#include "Core/Application.hpp"
#include "Core/Core.hpp"
#include "Core/Editor/ImGuiLayer.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Event/WindowEvent.hpp"
#include "Core/LayerStack.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/Renderer.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Editor/ImGuiLayer.hpp"

namespace WB
{

Application* Application::s_instance = nullptr;
float Application::m_dt = 1.0f / 60.0f;

Application::Application()
    : m_isRunning(true), m_layerStack(*this), m_isMinimized(false)
{

}

void Application::Start()
{
    CORE_LOG_SUCCESS("App is starting...");
    RenderCommand::Init();

    CreateWindow({.name = "WorldBuilder", .w = 1680, .h = 1050}, true);

    m_input = Input::Create();
    m_input->BindWindow(GetMainWindow());

    Renderer::Init();

    m_windows.front()->SetOnEventCallback(WB_BIND_FUN1(Application::OnEvent));
    m_windows.front()->PostCallback<WindowCloseEvent>(WB_BIND_FUN1(Application::OnApplicationCloseEvent), GetTypeID<Application>());
    m_windows.front()->PostCallback<WindowResizeEvent>(WB_BIND_FUN1(Application::OnApplicationResizeEvent), GetTypeID<Application>());

    RenderCommand::SetViewport(0, 0, 800, 640);
    RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f);

    ImGuiLayerBase::BaseInit();
}

void Application::Run()
{
    std::vector<SharedPtr<Layer>>& layers = m_layerStack.GetLayers();

    m_beginTick.ReadTime();

    while(m_isRunning)
    {
        for(auto& layer : layers)
        {
            layer->Update();
        }

        if(m_isMinimized) return;

        ImGuiLayerBase::Begin();
        for(auto& layer : layers)
        {
            layer->UpdateGUI();
        }
        ImGuiLayerBase::End();

        HandleSwapBuffers();
        HandleEvents();

        m_endTick.ReadTime();
        m_dt = static_cast<float>((m_endTick - m_beginTick).GetSeconds());
        m_beginTick = m_endTick;
        if(m_dt > 1.0f)
        {
            m_dt = 60.0f;
        }
    }
}

void Application::HandleEvents()
{
    for(auto& window : m_windows)
    {
        window->PollWindowEvents();
    }

    PollEvent();
}

void Application::HandleSwapBuffers()
{
    for(auto& window : m_windows)
    {
        window->SwapBuffers();
    }
}

void Application::Close()
{
    m_isRunning = false;
    CORE_LOG_SUCCESS("App has been stopped");
}

void Application::Shutdown()
{
    m_layerStack.ClearLayers();

    ImGuiLayerBase::BaseShutdown();

    for(auto& window : m_windows)
    {
        window->Shutdown();
    }

    Renderer::Shutdown();
    RenderCommand::Shutdown();

    CORE_LOG_SUCCESS("App has been shutdown");
}

void Application::OnEvent(Event& event)
{

}

void Application::OnApplicationCloseEvent(const WindowCloseEvent& event)
{
    PostTask(WB_BIND_FUN0(Application::Close));
}

void Application::OnApplicationResizeEvent(const WindowResizeEvent& event)
{
    if(event.Width == 0 || event.Height == 0)
    {
        m_isMinimized = true;
        return;
    }

    m_isMinimized = false;
    Renderer::OnWindowResize(event.Width, event.Height);
}

void Application::CreateWindow(const Window::WindowCreateData& windowData, bool isMainWindow)
{
    m_windows.push_back(Window::CreateWindow(windowData));

    if(isMainWindow)
    {
        m_mainWindowID = m_windows.size() - 1;
    }
}

}
