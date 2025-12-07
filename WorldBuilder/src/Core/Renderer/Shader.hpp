#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/Vertex.hpp"
#include <glm/glm.hpp>

namespace WB
{

class CustomShaderUniformBufferElement
{
public:
    CustomShaderUniformBufferElement(const std::string& type, const std::string& name, const std::string& displayName)
        : DisplayName(displayName), Name(name), Type(StringToShaderElement(type)), Data(nullptr)
    {
        DataSize = VertexBufferElement::ConvertShaderTypeToSize(Type);
    }

    ~CustomShaderUniformBufferElement()
    {
        if(Data)
        {
            free(Data);
        }
    }

    template<typename TType>
    void SetData(const TType& data)
    {
        WB_CORE_ASSERT(DataSize == sizeof(data), "given data does not have the right size");

        if(Data)
        {
            std::free(Data);
        }

        Data = std::malloc(sizeof(TType));
        std::memcpy(Data, &data, sizeof(TType));
    }

    void SetData(const void* data, size_t dataSize)
    {
        WB_CORE_ASSERT(DataSize == dataSize, "given data does not have the right size");

        if(Data)
        {
            std::free(Data);
        }

        Data = std::malloc(dataSize);
        std::memcpy(Data, data, dataSize);
    }

    WB_INLINE bool HasData() { return Data; }

    template<typename TData>
    WB_INLINE TData* GetData()
    {
        return static_cast<TData*>(Data);
    }

    template<typename TData>
    WB_INLINE const TData* GetData() const
    {
        return static_cast<const TData*>(Data);
    }

    WB_INLINE size_t GetDataSize() const { return DataSize; }

    WB_INLINE ShaderElementType GetType() const { return Type; }
    WB_INLINE const std::string& GetDisplayName() const { return DisplayName; }
    WB_INLINE const std::string& GetName() const { return Name; }

    static ShaderElementType StringToShaderElement(const std::string& type)
    {
        if(!std::strcmp(type.c_str(), "float"))
        {
            return ShaderElementType::Float;
        }
        else if(!std::strcmp(type.c_str(), "vec2"))
        {
            return ShaderElementType::Float2;
        }
        else if(!std::strcmp(type.c_str(), "vec3"))
        {
            return ShaderElementType::Float3;
        }
        else if(!std::strcmp(type.c_str(), "vec4"))
        {
             return ShaderElementType::Float4;
        }
        else if(!std::strcmp(type.c_str(), "mat3"))
        {
            return ShaderElementType::Mat3;
        }
        else if(!std::strcmp(type.c_str(), "mat4"))
        {
            return ShaderElementType::Mat4;
        }
        else if(!std::strcmp(type.c_str(), "int"))
        {
            return ShaderElementType::Int;
        }
        else if(!std::strcmp(type.c_str(), "sampler2D"))
        {
            return ShaderElementType::Sampler2D;
        }
        else
        {
            return ShaderElementType::Bool;
        }
    }

    bool Equal(ShaderElementType type, const std::string& displayName, const std::string& name)
    {
        return type == Type && displayName == DisplayName && name == Name;
    }

    static std::string ShaderElementToString(ShaderElementType type)
    {
        switch(type)
        {
            case ShaderElementType::Bool:
            {
                return "bool";
            }
            case ShaderElementType::Float:
            {
                return "float";
            }
            case ShaderElementType::Float2:
            {
                return "vec2";
            }
            case ShaderElementType::Float3:
            {
                return "vec3";
            }
            case ShaderElementType::Float4:
            {
                return "vec4";
            }
            case ShaderElementType::Int:
            {
                return "int";
            }
            case ShaderElementType::Int2:
            {
                return "ivec2";
            }
            case ShaderElementType::Int3:
            {
                return "ivec3";
            }
            case ShaderElementType::Int4:
            {
                return "ivec4";
            }
            case ShaderElementType::Mat3:
            {
                return "mat3";
            }
            case ShaderElementType::Mat4:
            {
                return "mat4";
            }
            case ShaderElementType::Sampler2D:
            {
                return "sampler2D";
            }

            default:
            {
                return "None";
            }
        }
    }

private:
    std::string DisplayName;
    std::string Name;
    void* Data;
    size_t DataSize;
    ShaderElementType Type;
};

class CustomShaderUniformBuffer
{
public:
    template<typename ... TArgs>
    CustomShaderUniformBufferElement& AddElement(TArgs&&... args) { return m_elements.emplace_back(std::forward<TArgs>(args)...); }
    WB_INLINE std::vector<CustomShaderUniformBufferElement>& GetElements() { return m_elements; }
    WB_INLINE const std::vector<CustomShaderUniformBufferElement>& GetElements() const { return m_elements; }
    WB_INLINE void AddElements(const CustomShaderUniformBuffer& elementsBuffer)
    {
        if(elementsBuffer.m_elements.size() > 0)
        {
            AddElements(elementsBuffer.m_elements);
        }
    }
    WB_INLINE void AddElements(const std::vector<CustomShaderUniformBufferElement>& elements)
    {
        m_elements.insert(m_elements.end(), elements.begin(), elements.end());
    }

    WB_INLINE void ClearElements()
    {
        m_elements.clear();
    }


private:
    std::vector<CustomShaderUniformBufferElement> m_elements;
};


enum class ShaderType
{
    NONE,
    VERTEX,
    FRAGMENT
};

class Shader : public Asset
{
public:
    virtual ~Shader() = default;

    bool LoadShader(const Path& shaderPath);
    bool UnLoadShader();
    virtual bool CompileShader() = 0;

    WB_INLINE virtual uint32_t GetShaderID() const = 0;

    static SharedPtr<Shader> Create();

    CustomShaderUniformBuffer GetCustomUniformTemplateCopy() { return m_customUniformTemplate; }
    ShaderType GetType() { return m_shaderType; }

private:
    virtual bool CreateShaderData() = 0;
    virtual void DestroyShaderData() = 0;

protected:
    std::string m_shaderData;
    CustomShaderUniformBuffer m_customUniformTemplate;
    ShaderType m_shaderType = ShaderType::NONE;
};

}
