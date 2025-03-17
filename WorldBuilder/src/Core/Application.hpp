#pragma once

namespace WB
{

class Application
{
public:
    Application() = default;
    ~Application() = default;

    void Start();
    void Run();
    void Shutdown();
};

}
