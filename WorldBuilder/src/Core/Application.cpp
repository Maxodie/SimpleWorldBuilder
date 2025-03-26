#include "Core/Application.hpp"
#include "Core/Core.hpp"
#include "Core/LayerStack.hpp"

namespace WB
{
class LayerTest : public Layer
{
public:
    LayerTest(TypeID id)
        : Layer(id)
    {

    }

    void Update() override
    {
    }

    virtual void OnAttach() override
    {

    }
    virtual void OnDettach() override
    {

    }
};

Application::Application()
    : m_isRunning(true), m_layerStack()
{

}

void Application::Start()
{
    CORE_LOG_SUCCESS("App has been started");
    m_layerStack.AddLayer<LayerTest>(GetTypeID<LayerTest>());
}

void Application::Run()
{
    std::vector<Layer*>& layers = m_layerStack.GetLayers();
    while(m_isRunning)
    {
        for(auto& layer : layers)
        {
            layer->Update();
        }
    }
}

void Application::Shutdown()
{
    m_isRunning = false;
    CORE_LOG_SUCCESS("App has been shut down");
}

}
