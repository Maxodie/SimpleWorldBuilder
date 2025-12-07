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

static constexpr glm::vec2 ConvertAiToGlmVec2(aiVector3D& vec3)
{
    return {vec3.x, vec3.y};
}

static Mesh ProcessMesh(struct aiMesh* mesh, const struct aiScene* scene, bool shouldInverseVerticalTexCoords)
{
    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;
    bool hasTexCoords = mesh->mTextureCoords[0];

    for(uint32_t i=0; i < mesh->mNumVertices;  i++)
    {
        vertices.emplace_back();
        vertices[i].Position = ConvertAiToGlmVec3(mesh->mVertices[i]);
        vertices[i].Normal = ConvertAiToGlmVec3(mesh->mNormals[i]);

        if(hasTexCoords)
        {
            if(shouldInverseVerticalTexCoords)
            {
                mesh->mTextureCoords[0][i].y *= -1;
                vertices[i].TexCoords = ConvertAiToGlmVec2(mesh->mTextureCoords[0][i]);
            }
            else
            {
                vertices[i].TexCoords = ConvertAiToGlmVec2(mesh->mTextureCoords[0][i]);
            }
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

    return Mesh(vertices, indices);
}

static void ProcessNode(std::vector<Mesh>& Meshes, struct aiNode* node, const struct aiScene* scene, bool shouldInverseVerticalTexCoords)
{
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Meshes.push_back(ProcessMesh(mesh, scene, shouldInverseVerticalTexCoords));
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(Meshes, node->mChildren[i], scene, shouldInverseVerticalTexCoords);
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
    bool shouldInverseVerticalTexCoords = FileSystem::HasExtension(path, ".obj");
    ProcessNode(modelAsset.meshes, scene->mRootNode, scene, shouldInverseVerticalTexCoords);
    return true;
}

}
