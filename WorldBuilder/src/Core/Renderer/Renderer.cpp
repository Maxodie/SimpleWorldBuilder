#include "Core/Renderer/Renderer.hpp"
#include "Core/Renderer/Renderer3D.hpp"

namespace WB
{

void Renderer::Init()
{
    Renderer3D::Init();

    CORE_LOG_SUCCESS("Renderer has been initialized");
}

void Renderer::Shutdown()
{
    Renderer3D::Shutdown();
    CORE_LOG_SUCCESS("Renderer has been shutted down");
}

}
