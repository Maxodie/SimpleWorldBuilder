#include "Core/Renderer/VertexBuffer.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Vertex.hpp"
#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/Renderer/Opengl/OpenglVertexBuffer.hpp"

namespace WB
{

template<typename TVertex>
VertexBuffer<TVertex>::VertexBuffer(size_t startBufferSize)
    : m_vertices((TVertex*)malloc(startBufferSize * sizeof(TVertex))), m_verticiesCount{0}
{
}

template<typename TVertex>
VertexBuffer<TVertex>::~VertexBuffer()
{
    WB_DELETE(m_vertices);
}

template<typename TVertex>
void VertexBuffer<TVertex>::AddVertex(TVertex& vertex)
{
    *m_vertices = vertex;
    m_verticiesCount++;
}

template<typename TVertex>
SharedPtr<VertexBuffer<TVertex>> VertexBuffer<TVertex>::Create(size_t bufferSize)
{
    switch (RenderCommand::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return MakeShared<OpenglVertexBuffer<TVertex>>(bufferSize);
        break;

        case RendererAPI::API::None:
            CORE_LOG_ERROR("Unknown RendererAPI : %d", RenderCommand::GetAPI());
        break;

        default:
            CORE_LOG_ERROR("Unknown RendererAPI : %d", RenderCommand::GetAPI());
        break;
    }

    return nullptr;
}

template class VertexBuffer<Vertex3D>;

}
