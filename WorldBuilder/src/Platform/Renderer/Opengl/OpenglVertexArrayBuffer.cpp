#include "Platform/Renderer/Opengl/OpenglVertexArrayBuffer.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/Buffer.hpp"

namespace WB
{

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderElementType type)
{
    switch (type)
    {
        case ShaderElementType::Float: return GL_FLOAT;
        case ShaderElementType::Float2:	return GL_FLOAT;
        case ShaderElementType::Float3:	return GL_FLOAT;
        case ShaderElementType::Float4:	return GL_FLOAT;
        case ShaderElementType::Mat3: return GL_FLOAT;
        case ShaderElementType::Mat4: return GL_FLOAT;
        case ShaderElementType::Int: return GL_INT;
        case ShaderElementType::Int2: return GL_INT;
        case ShaderElementType::Int3: return GL_INT;
        case ShaderElementType::Int4: return GL_INT;
        case ShaderElementType::Bool: return GL_BOOL;
        case ShaderElementType::Sampler2D: return GL_SAMPLER_2D;
    }

    CORE_LOG_ERROR("Unknown ShaderDataType %d", type);
    return 0;
}

template<typename TVertex>
void OpenglVertexArrayBuffer<TVertex>::AddVertexBuffer(SharedPtr<VertexBuffer<TVertex>>& vertexBuffer)
{
    Bind();
    vertexBuffer->BindBuffer();

    uint32_t i = 0;

    auto& elements = vertexBuffer->GetLayout().GetElements();
    for(auto& element : elements)
    {
        glEnableVertexAttribArray(i);

        glVertexAttribPointer(
            i,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.IsNormalized ? GL_TRUE : GL_FALSE,
            vertexBuffer->GetLayout().GetStride(),
            (void*)element.Offset
        );

        i++;
    }

    OpenglVertexArrayBuffer<TVertex>::m_layout.push_back(vertexBuffer);
}

template class OpenglVertexArrayBuffer<Vertex3D>;

}
