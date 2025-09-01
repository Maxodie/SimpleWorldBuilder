#pragma once
#include "Core/Core.hpp"
#include "Core/AssetManager/Asset.hpp"

#include "glm/ext/vector_float3.hpp"
#include "yaml-cpp/yaml.h"

namespace WB
{

class Serializer
{
public:
    Serializer() = delete;

    static YAML::Node encode(const glm::vec3& rhs);
    static bool decode(const YAML::Node& node, glm::vec3& rhs);

    static std::string AssetTypeAsString(AssetType type);
    static AssetType AssetStringAsType(std::string type);
};


WB_INLINE YAML::Emitter& operator<<(YAML::Emitter& emitter, const glm::vec3& v)
{
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return emitter;
}

}
