#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Vertex.hpp"
#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/Renderer/Opengl/OpenglBuffer.hpp"

namespace WB
{

template<typename TVertex>
Buffer<TVertex>::Buffer(size_t startBufferCount)
    : m_values((TVertex*)malloc(startBufferCount * sizeof(TVertex))), m_valuesCount{0}
{
}

template<typename TVertex>
Buffer<TVertex>::~Buffer()
{
    WB_DELETE(m_values);
}

template<typename TVertex>
void Buffer<TVertex>::AddValue(TVertex& value)
{
    m_values[m_valuesCount] = value;
    m_valuesCount++;
}

template<typename TVertex>
void Buffer<TVertex>::ResetBuffer()
{
    m_valuesCount = 0;
}

template class Buffer<Vertex3D>;
template class Buffer<uint32_t>;

// VERTEX BUFFER
template<typename TVertex>
VertexBuffer<TVertex>::VertexBuffer(size_t startBufferCount)
: Buffer<TVertex>(startBufferCount)
{

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

// INDEX BUFFER
template<typename TIndex>
IndexBuffer<TIndex>::IndexBuffer(size_t startBufferCount)
: Buffer<TIndex>(startBufferCount)
{

}

template<typename TIndex>
SharedPtr<IndexBuffer<TIndex>> IndexBuffer<TIndex>::Create(size_t bufferSize)
{
    switch (RenderCommand::GetAPI()) {
        case RendererAPI::API::OpenGL:
            return MakeShared<OpenglIndexBuffer<TIndex>>(bufferSize);
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

template class IndexBuffer<uint32_t>;

}
