#pragma once

#include "Core/LayerStack.hpp"

namespace WB
{

class Application
{
public:
    Application();
    ~Application() = default;

    void Start();
    void Run();
    void Shutdown();

private:
    bool m_isRunning;
    LayerStack m_layerStack;
};

}
