#pragma once
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include <glm/glm.hpp>

namespace WB
{

enum class ShaderElementType
{
    Bool,
    Float, Float2, Float3, Float4,
    Int, Int2, Int3, Int4,
    Mat3, Mat4,
    Sampler2D
};

struct VertexBufferElement
{
    std::string Name;
    size_t Size;
    ShaderElementType Type;
    bool IsNormalized;
    size_t Offset;

    VertexBufferElement(std::string name, ShaderElementType shaderType, bool isNormalized = false)
        : Size(ConvertShaderTypeToSize(shaderType)), IsNormalized(isNormalized), Offset(0), Type(shaderType), Name(name)
    {

    }

    uint32_t GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderElementType::Float: return 1;
            case ShaderElementType::Float2:	return 2;
            case ShaderElementType::Float3:	return 3;
            case ShaderElementType::Float4:	return 4;
            case ShaderElementType::Mat3: return 3 * 3;
            case ShaderElementType::Mat4: return 4 * 4;
            case ShaderElementType::Int: return 1;
            case ShaderElementType::Int2: return 2;
            case ShaderElementType::Int3: return 3;
            case ShaderElementType::Int4: return 4;
            case ShaderElementType::Bool: return 1;
            case ShaderElementType::Sampler2D: return 1;
        }

        CORE_LOG_ERROR("unknown Type : %d", Type);
        return 0;
    }

    static size_t ConvertShaderTypeToSize(ShaderElementType shaderType)
    {
        switch(shaderType)
        {
            case ShaderElementType::Bool : return 1;
            case ShaderElementType::Float : return 4;
            case ShaderElementType::Float2 : return 4 * 2;
            case ShaderElementType::Float3 : return 4 * 3;
            case ShaderElementType::Float4 : return 4 * 4;
            case ShaderElementType::Int : return 4;
            case ShaderElementType::Int2 : return 4 * 2;
            case ShaderElementType::Int3 : return 4 * 3;
            case ShaderElementType::Int4 : return 4 * 4;
            case ShaderElementType::Mat3 : return 4 * 3 * 3;
            case ShaderElementType::Mat4 : return 4 * 4 * 4;
            case ShaderElementType::Sampler2D : return sizeof(AssetID);
        }

        CORE_LOG_ERROR("unknown given ShaderType : %d", shaderType);
        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<VertexBufferElement>& elements)
        : m_elements(elements)
    {
        CalculateStrideAndOffset();
    }

    [[nodiscard]] WB_INLINE size_t GetStride() { return m_stride; }

    WB_INLINE const std::vector<VertexBufferElement>& GetElements() { return m_elements; }

private:
    void CalculateStrideAndOffset()
    {
        uint32_t offset = 0;
        m_stride = 0;
        for(auto& element : m_elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_stride += element.Size;
        }
    }

    size_t m_stride = 0;
    std::vector<VertexBufferElement> m_elements;
};

struct Vertex3D
{
    Vertex3D() = default;

    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Normal = glm::vec3(0.0f);
    glm::vec2 TexCoords = glm::vec2(0.0f, 1.0f);
};

template<typename TVertex>
class VertexBuffer;

template<typename TVertex>
class VertexArrayBuffer
{
public:
    VertexArrayBuffer() = default;

    virtual void AddVertexBuffer(SharedPtr<VertexBuffer<TVertex>>& vertexBuffer) = 0;
    WB_INLINE virtual void Bind() = 0;

    [[nodiscard]] WB_INLINE std::vector<SharedPtr<VertexBuffer<TVertex>>>& GetLayout()
    {
        return m_layout;
    }

    static SharedPtr<VertexArrayBuffer<TVertex>> Create();

protected:
    std::vector<SharedPtr<VertexBuffer<TVertex>>> m_layout;
};

}
