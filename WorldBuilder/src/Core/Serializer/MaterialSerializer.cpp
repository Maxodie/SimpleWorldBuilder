#include "Core/Serializer/MaterialSerializer.hpp"
#include "Core/Project.hpp"
#include "Core/Serializer/Serializer.hpp"
#include "Core/Renderer/Material.hpp"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/yaml.h"

namespace WB
{
bool MaterialSerializer::Serialize(const Material& material, const Path& path)
{
    YAML::Emitter emitter;

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "id" << YAML::Value << material.id;
    emitter << YAML::Key << "color" << YAML::Value << Serializer::Encode(material.GetAlbedoColor());

    AssetID texID = EMPTY_ASSET;
    if(material.GetAlbedoTexture().lock())
    {
        texID = material.GetAlbedoTexture().lock()->id;
    }

    emitter << YAML::Key << "albedo_tex_id" << YAML::Value << texID;
    emitter << YAML::EndMap;

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

        if(root["id"])
        {
            material.id = root["id"].as<AssetID>();
        }

        if(root["color"])
        {
            glm::vec4 color;
            if(Serializer::Decode(root["color"], color))
            {
                material.SetAlbedoColor(color);
            }
        }

        if(root["albedo_tex_id"])
        {
            material.SetTexture(Project::GetActive()->GetAssetManager()->GetAsset<Texture2D>(root["albedo_tex_id"].as<AssetID>()));
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
