#include "Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.hpp"
#include "Core/Core.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace WB
{

OpenglGLFWGraphicsContext::OpenglGLFWGraphicsContext()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
}

void OpenglGLFWGraphicsContext::InitGraphicsContext()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        WB_CORE_ASSERT(false, "failed to init GLAD");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);
}

void OpenglGLFWGraphicsContext::ShutdownGraphicsContext()
{

}

}
