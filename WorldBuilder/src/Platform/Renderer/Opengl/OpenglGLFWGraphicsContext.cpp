#include "Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.hpp"
#include "Core/Core.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace WB
{

void OpenglGLFWGraphicsContext::InitGraphicsContext()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        WB_CORE_ASSERT(false, "failed to init GLAD");
    }
}

void OpenglGLFWGraphicsContext::ShutdownGraphicsContext()
{

}

}
