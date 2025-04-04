#include "Core/Application.hpp"

extern void OnAppStarted(WB::Application& app);

int main()
{
    WB::Application app;

    app.Start();
    OnAppStarted(app);

    app.Run();
    app.Shutdown();
}
