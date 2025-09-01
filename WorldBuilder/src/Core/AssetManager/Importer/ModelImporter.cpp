#include "Core/AssetManager/Importer/ModelImporter.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace WB
{

static constexpr glm::vec3 ConvertAiToGlmVec3(aiVector3D& vec3)
{
    return {vec3.x, vec3.y, vec3.z};
}

static constexpr glm::vec2 ConvertAiToGlmTexCoords(aiVector3D& vec3)
{
    return {vec3.x, vec3.y};
}

static Mesh ProcessMesh(struct aiMesh* mesh, const struct aiScene* scene)
{
    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;
    bool hasTexCoords = mesh->mTextureCoords[0];

    for(uint32_t i=0; i < mesh->mNumVertices;  i++)
    {
        if(hasTexCoords)
        {
            vertices.emplace_back(ConvertAiToGlmVec3(mesh->mVertices[i]), ConvertAiToGlmTexCoords(mesh->mTextureCoords[0][i]));
        }
        else
        {
            vertices.emplace_back(ConvertAiToGlmVec3(mesh->mVertices[i]));
        }
    }

    for(uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(uint32_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    /*if(mesh->mMaterialIndex >= 0)*/
    /*{*/
    /**/
    /*}*/

    return Mesh(vertices, indices);
}

static void ProcessNode(std::vector<Mesh>& Meshes, struct aiNode* node, const struct aiScene* scene)
{
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Meshes.push_back(ProcessMesh(mesh, scene));
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(Meshes, node->mChildren[i], scene);
    }
}

bool ModelImporter::Importe(const Path& path, ModelAsset& modelAsset)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        CORE_LOG_ERROR("assimp : %s", importer.GetErrorString());
        return false;
    }

    ProcessNode(modelAsset.data.Meshes, scene->mRootNode, scene);
    return true;
}

}
