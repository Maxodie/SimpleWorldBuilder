#include "Core/Serializer/Serializer.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Renderer/Model.hpp"

namespace WB
{

YAML::Node Serializer::encode(const glm::vec3& rhs)
{
    YAML::Node node;
    node.push_back(rhs.x);
    node.push_back(rhs.y);
    node.push_back(rhs.z);
    return node;
}

bool Serializer::decode(const YAML::Node& node, glm::vec3& rhs)
{
    if(!node.IsSequence() || node.size() != 3)
    {
        return false;
    }

    rhs.x = node[0].as<float>();
    rhs.y = node[1].as<float>();
    rhs.z = node[2].as<float>();

    return true;
}

//INFO COMP
YAML::Node Serializer::EncodeInfo(const InfoComponent& info)
{
    YAML::Node node;
    node.push_back(info.name);
    node.push_back(static_cast<uint32_t>(info.handle));
    node.push_back(static_cast<uint32_t>(info.parent));
    return node;
}

bool Serializer::DecodeInfo(InfoComponent& info, const YAML::Node& node)
{
    if(!node.IsSequence() || node.size() != 3)
    {
        return false;
    }

    info.name = node[0].as<std::string>();
    info.handle = static_cast<EntityHandle>(node[1].as<uint32_t>());
    info.parent = static_cast<EntityHandle>(node[2].as<uint32_t>());
    return true;
}

// TRANFORM COMP
YAML::Node Serializer::EncodeTransform(const TransformComponent& transform)
{
    YAML::Node node;
    node.push_back(encode(transform.GetPosition()));
    node.push_back(encode(transform.GetRotation()));
    node.push_back(encode(transform.GetScale()));
    return node;
}

bool Serializer::DecodeTransform(TransformComponent& transform, const YAML::Node& node)
{
    if(!node.IsSequence() || node.size() != 3)
    {
        return false;
    }

    glm::vec3 vec;

    decode(node[0], vec);
    transform.SetPosition(vec);

    decode(node[1], vec);
    transform.SetRotation(vec);

    decode(node[2], vec);
    transform.SetScale(vec);

    return true;
}
//

std::string Serializer::AssetTypeAsString(AssetType type)
{
    switch(type)
    {
        case AssetType::MODEL: return "Model";
        case AssetType::SHADER: return "Shader";
        case AssetType::SCENE: return "Scene";
        case AssetType::TEXTURE: return "Texture";
        case AssetType::MATERIAL: return "Material";
        case AssetType::FOLDER: return "Folder";
        case AssetType::UNKNOWN: return "Unknown";

        default:
        {
            CORE_LOG_ERROR("Undefined asset type %s", type);
            return "Undefined";
        }
    }
}

AssetType Serializer::AssetStringAsType(std::string type)
{
    if(type == "Model")
    {
        return AssetType::MODEL;
    }
    else if(type == "Shader")
    {
        return AssetType::SHADER;
    }
    else if(type == "Scene")
    {
        return AssetType::SCENE;
    }
    else if(type == "Texture")
    {
        return AssetType::TEXTURE;
    }
    else if(type == "Folder")
    {
        return AssetType::FOLDER;
    }
    else if(type == "Unknown")
    {
        return AssetType::UNKNOWN;
    }

    CORE_LOG_ERROR("Undefined asset type %s", type.c_str());
    return AssetType::UNKNOWN;
}

}
