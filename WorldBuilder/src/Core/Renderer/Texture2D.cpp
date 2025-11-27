#include "Core/Renderer/Texture2D.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/Renderer/Opengl/OpenglTexture2D.hpp"

namespace WB
{

Texture2D::Texture2D(uint32_t width, uint32_t height)
    : m_width(width), m_height(height)
{

}

SharedPtr<Texture2D> Texture2D::CreateTexture(uint32_t width, uint32_t height)
{
    switch (RenderCommand::GetAPI())
    {
        case RendererAPI::API::None:
        {
            break;
        }

        case RendererAPI::API::OpenGL:
        {
            return MakeShared<OpenglTexture2D>(width, height);
            break;
        }
    }

    return nullptr;
}

SharedPtr<Texture2D> Texture2D::CreateTexture(const Path& path)
{
    switch (RenderCommand::GetAPI())
    {
        case RendererAPI::API::None:
        {
            break;
        }

        case RendererAPI::API::OpenGL:
        {
            return MakeShared<OpenglTexture2D>(path);
            break;
        }
    }

    return nullptr;
}

}
