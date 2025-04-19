#include "Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace WB
{

static void GLAPIENTRY OpenglMessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* useParam
)
{
    switch(type)
    {
        case GL_DEBUG_TYPE_ERROR:
            CORE_LOG_ERROR("OpenGL : type = 0x%x, severity = 0x%x, message = %s", type, severity, message);
        break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            CORE_LOG_WARNING("OpenGL : type = 0x%x, severity = 0x%x, message = %s", type, severity, message);
        break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            CORE_LOG_WARNING("OpenGL : type = 0x%x, severity = 0x%x, message = %s", type, severity, message);
        break;
        case GL_DEBUG_TYPE_PORTABILITY:
            CORE_LOG_DEBUG("OpenGL : type = 0x%x, severity = 0x%x, message = %s", type, severity, message);
        break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            CORE_LOG_DEBUG("OpenGL : type = 0x%x, severity = 0x%x, message = %s", type, severity, message);
        break;
        case GL_DEBUG_TYPE_OTHER:
            CORE_LOG_DEBUG("OpenGL : type = 0x%x, severity = 0x%x, message = %s", type, severity, message);
        break;
    }
}

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

    glEnable(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpenglMessageCallback, (void*)0);
}

void OpenglGLFWGraphicsContext::ShutdownGraphicsContext()
{

}

}
