#include "Core/Application.hpp"

extern void OnAppStarted(WB::Application& app);

int main()
{
    WB::Application& app = WB::Application::Create();

    app.Start();
    OnAppStarted(app);

    app.Run();
    app.Shutdown();

    app.Destroy();
}
