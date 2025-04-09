#include "Core/Core.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Platform/Renderer/Opengl/OpenglVertexArrayBuffer.hpp"

namespace WB
{

template<typename TVertex>
SharedPtr<VertexArrayBuffer<TVertex>> VertexArrayBuffer<TVertex>::Create()
{
    switch (RenderCommand::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_LOG_ERROR("failed to create Vertex Array Buffer, unknown renderer api : %d", RenderCommand::GetAPI());
        break;

        case RendererAPI::API::OpenGL:
            return MakeShared<OpenglVertexArrayBuffer<TVertex>>();
        break;

        default:
            CORE_LOG_ERROR("failed to create Vertex Array Buffer, unknown renderer api : %d", RenderCommand::GetAPI());
        break;
    }
    return nullptr;
}

template class VertexArrayBuffer<Vertex3D>;

}
