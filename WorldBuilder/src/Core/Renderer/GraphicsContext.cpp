#include "Core/Renderer/GraphicsContext.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Window/Window.hpp"
#include "Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.hpp"

namespace WB
{

UniquePtr<GraphicsContext> GraphicsContext::CreateContext()
{
    if(RenderCommand::GetAPI() == RendererAPI::API::OpenGL && Window::GetAPI() == Window::API::GLFW)
    {
        return MakeUnique<OpenglGLFWGraphicsContext>();
    }

    return nullptr;
}

}
