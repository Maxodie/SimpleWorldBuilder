#include "Core/Application.hpp"

int main()
{
    WB::Application app;

    app.Start();
    app.Run();
    app.Shutdown();
}
