#pragma once
#include "Core/Core.hpp"
#include "Core/AssetManager/Asset.hpp"

#include "Core/Log/Log.hpp"
#include "glm/ext/vector_float3.hpp"
#include "yaml-cpp/yaml.h"

namespace WB
{

class Serializer
{
public:
    Serializer() = delete;

    static YAML::Node Encode(const glm::vec4& rhs);
    static bool Decode(const YAML::Node& node, glm::vec4& rhs);
    static YAML::Node Encode(const glm::vec3& rhs);
    static bool Decode(const YAML::Node& node, glm::vec3& rhs);
    static YAML::Node Encode(const glm::vec2& rhs);
    static bool Decode(const YAML::Node& node, glm::vec2& rhs);

    //components
    static YAML::Node EncodeInfo(const class InfoComponent& info);
    static bool DecodeInfo(InfoComponent& info, const YAML::Node& node);

    static YAML::Node EncodeTransform(const class TransformComponent& transform);
    static bool DecodeTransform(TransformComponent& transform, const YAML::Node& node);

    static YAML::Node EncodePointLight(const class PointLightComponent& pointLight);
    static bool DecodePointLight(class PointLightComponent& pointLight, const YAML::Node& node);
    //

    static std::string AssetTypeAsString(AssetType type);
    static AssetType AssetStringAsType(std::string type);

    template<typename TType>
    static TType GetData(const YAML::Node& node, const std::string& key)
    {
        if(node[key])
        {
            return node[key].as<TType>();
        }
        else
        {
            CORE_LOG_WARNING("could not read the data, returning default value");
            return TType{};
        }
    }
};


WB_INLINE YAML::Emitter& operator<<(YAML::Emitter& emitter, const glm::vec3& v)
{
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return emitter;
}

}
