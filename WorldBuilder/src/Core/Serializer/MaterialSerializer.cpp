#include "Core/Serializer/MaterialSerializer.hpp"
#include "Core/Core.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Serializer/Serializer.hpp"
#include "Core/Renderer/Material.hpp"
#include "yaml-cpp/binary.h"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/yaml.h"

namespace WB
{
bool MaterialSerializer::Serialize(const Material& material, const Path& path)
{
    YAML::Emitter emitter;

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "id" << YAML::Value << material.id;

    AssetID shaderID = EMPTY_ASSET;
    if(material.GetFragmentShader().lock())
    {
        shaderID = material.GetFragmentShader().lock()->id;
    }
    emitter << YAML::Key << "fragment_shader" << YAML::Value << shaderID;

    if(material.GetVertexShader().lock())
    {
        shaderID = material.GetVertexShader().lock()->id;
    }
    emitter << YAML::Key << "vertex_shader" << YAML::Value << shaderID;

    emitter << YAML::Key << "layout" << YAML::Value << YAML::BeginSeq;

    const CustomShaderUniformBuffer& customLayout = material.GetCustomBufferLayout();
    for(const auto& element : customLayout.GetElements())
    {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "display_name" << YAML::Value << element.GetDisplayName();
        emitter << YAML::Key << "name" << YAML::Value << element.GetName();
        emitter << YAML::Key << "data_size" << YAML::Value << element.GetDataSize();

        if(element.GetData<const unsigned char>())
        {
            emitter << YAML::Key << "data" << YAML::Value << YAML::Binary(element.GetData<const unsigned char>(), element.GetDataSize());
        }

        emitter << YAML::Key << "type" << YAML::Value << CustomShaderUniformBufferElement::ShaderElementToString(element.GetType());
        emitter << YAML::EndMap;
    }
    emitter << YAML::EndSeq;

    return FileSystem::SyncWriteAtPathAsString(path, emitter.c_str());
}

bool MaterialSerializer::Deserialize(Material& material, const Path& path)
{
    if(!FileSystem::Exists(path))
    {
        return false;
    }

    try
    {
        YAML::Node root = YAML::LoadFile(path.string());
        if(root.IsNull())
        {
            CORE_LOG_ERROR("failed to parse %s", path.string().c_str());
            return false;
        }

        material.id = Serializer::GetData<AssetID>(root, "id");

        AssetID fragmentShaderID = Serializer::GetData<AssetID>(root, "fragment_shader");
        AssetID vertexShaderID = Serializer::GetData<AssetID>(root, "vertex_shader");
        WeakPtr<Shader> fragmentShader, vertexShader;
        if(fragmentShaderID != EMPTY_ASSET)
        {
            fragmentShader = Project::GetActive()->GetAssetManager()->GetAsset<Shader>(fragmentShaderID);
        }
        if(vertexShaderID != EMPTY_ASSET)
        {
            vertexShader = Project::GetActive()->GetAssetManager()->GetAsset<Shader>(vertexShaderID);
        }

        material.Load(vertexShader, fragmentShader);

        if(root["layout"])
        {
            CustomShaderUniformBuffer& customLayoutBuffer = material.GetCustomBufferLayout();
            for(const auto& node : root["layout"])
            {
                for(auto& matElement : customLayoutBuffer.GetElements())
                {
                    std::string name = Serializer::GetData<std::string>(node, "name");
                    std::string type = Serializer::GetData<std::string>(node, "type");
                    std::string displayName = Serializer::GetData<std::string>(node, "display_name");
                    if(matElement.Equal(CustomShaderUniformBufferElement::StringToShaderElement(type), displayName, name))
                    {
                        YAML::Binary data = Serializer::GetData<YAML::Binary>(node, "data");
                        matElement.SetData(data.data(), matElement.GetDataSize());
                    }
                }
            }
        }

        return true;
    }
    catch(const YAML::ParserException& ex)
    {
        CORE_LOG_ERROR("failed to parse %s || %s", path.string().c_str(), ex.what());
        return false;
    }
}

}
