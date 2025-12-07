#include "Core/Renderer/Material.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"
#include "Core/Renderer/Renderer3D.hpp"

namespace WB
{

Material::Material()
    : m_shaderProgram(nullptr), m_vertexShader({}), m_fragmentShader({})
{

}

Material::~Material()
{
    Renderer3D::ShutdownShaderProgram(m_shaderProgram);
}

void Material::Load(WeakPtr<Shader> vertex, WeakPtr<Shader> fragment)
{
    if(!m_shaderProgram)
    {
        m_shaderProgram = ShaderProgram::Create();
        Renderer3D::InitShaderProgram(m_shaderProgram);
    }

    if(m_vertexShader)
    {
        CORE_LOG_DEBUG("Detach last vertex shader");
        m_shaderProgram->DetachShader(*m_vertexShader);
    }

    if(vertex.lock())
    {
        m_vertexShader = static_pointer_cast<Shader>(vertex.lock());
        m_shaderProgram->AttachShader(*m_vertexShader);
    }
    else
    {
        m_vertexShader = nullptr;
    }

    if(m_fragmentShader)
    {
        CORE_LOG_DEBUG("Detach last fragment shader");
        m_shaderProgram->DetachShader(*m_fragmentShader);
    }

    if(fragment.lock())
    {
        m_fragmentShader = static_pointer_cast<Shader>(fragment.lock());
        m_shaderProgram->AttachShader(*m_fragmentShader);
    }
    else
    {
        m_fragmentShader = nullptr;
    }

    m_customUniformbufferLayout.ClearElements();

    if(m_vertexShader)
    {
        m_customUniformbufferLayout.AddElements(m_vertexShader->GetCustomUniformTemplateCopy());
    }
    if(m_fragmentShader)
    {
        m_customUniformbufferLayout.AddElements(m_fragmentShader->GetCustomUniformTemplateCopy());
    }

    if(m_vertexShader && m_fragmentShader)
    {
        m_shaderProgram->Link();
        Renderer3D::SetupShaderProgramUniforms(m_shaderProgram);
    }
}

void Material::Bind()
{
    std::vector<CustomShaderUniformBufferElement>& elements = m_customUniformbufferLayout.GetElements();
    for(auto& element : elements)
    {
        if(!element.HasData())
        {
            continue;
        }

        switch (element.GetType()) {
            case ShaderElementType::Float:
            {
                m_shaderProgram->SetFloat(element.GetName(), *element.GetData<float>());
                break;
            }
            case ShaderElementType::Float2:
            {
                m_shaderProgram->SetFloat2(element.GetName(), *element.GetData<glm::vec2>());
                break;
            }
            case ShaderElementType::Float3:
            {
                m_shaderProgram->SetFloat3(element.GetName(), *element.GetData<glm::vec3>());
                break;
            }
            case ShaderElementType::Float4:
            {
                m_shaderProgram->SetFloat4(element.GetName(), *element.GetData<glm::vec4>());
                break;
            }
            case ShaderElementType::Mat3:break;
            case ShaderElementType::Mat4:break;
            case ShaderElementType::Int:break;
            case ShaderElementType::Int2:break;
            case ShaderElementType::Int3:break;
            case ShaderElementType::Int4:break;
            case ShaderElementType::Bool:break;
            case ShaderElementType::Sampler2D:
            {
                // const SharedPtr<Texture2D>* tex = static_cast<const SharedPtr<Texture2D>*>(element.GetData());
                if(*element.GetData<AssetID>() != EMPTY_ASSET)
                {
                    const WeakPtr<Texture2D> tex = Project::GetActive()->GetAssetManager()->GetAsset<Texture2D>(*element.GetData<AssetID>());
                    if(tex.lock())
                    {
                        float texID = static_cast<float>(Renderer3D::AddDrawTexture(tex.lock()));
                        m_shaderProgram->SetFloat(element.GetName(), texID);
                    }
                }

                break;
            }
        }
    }
}

}
