#include "Core/Renderer/FrameBuffer.hpp"
#include "Core/Core.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Platform/Renderer/Opengl/OpenglFrameBuffer.hpp"

namespace WB
{

SharedPtr<FrameBuffer> FrameBuffer::Create()
{
    switch(RenderCommand::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return MakeShared<OpenglFrameBuffer>();
        break;
        case RendererAPI::API::None:
            CORE_LOG_ERROR("None RendererAPI %d", RenderCommand::GetAPI());
        break;
        default:
            CORE_LOG_ERROR("invalide RendererAPI %d", RenderCommand::GetAPI());
        break;
    }

    return nullptr;
}

}
