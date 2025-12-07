#include "UIEditor/Inspector/AssetInspector.hpp"
#include "Core/AssetManager/Engine/EngineAssetManager.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Serializer/MaterialSerializer.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace WB
{

void SceneAssetInspector::Show(SharedPtr<AssetMetaData> metaData)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if(!metaData)
    {
        ImGui::Text("Scene meta data error");
        return;
    }

    ImGui::Text(("Scene : " + metaData->name).c_str());

    if(ImGui::Button("Delete"))
    {
        Project::GetActive()->GetEditorAssetManager()->DeleteMeta(metaData);
        Project::GetActive()->GetAssetManager()->CheckPackagesValidity();
    }

    ImGui::PopStyleVar();
}

void MaterialAssetInspector::Show(SharedPtr<AssetMetaData> metaData, Application& context)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if(!metaData)
    {
        ImGui::Text("Material meta data error");
        return;
    }

    ImGui::Text(("Material : " + metaData->name).c_str());

    WeakPtr<Material> mat = Project::GetActive()->GetAssetManager()->GetAsset<Material>(metaData->id);
    if(!mat.lock())
    {
        CORE_LOG_ERROR("Material not found !");
        return;
    }

    Material& matRef = *mat.lock();

    std::string shaderName = "None";
    if(matRef.GetFragmentShader().lock())
    {
        WeakPtr<AssetMetaData> shaderMeta = Project::GetActive()->GetEditorAssetManager()->GetMetaData(matRef.GetFragmentShader().lock()->id);
        if(shaderMeta.lock())
        {
            shaderName = shaderMeta.lock()->name;
        }
    }

    if(ImGui::Button(("Fragment Shader : " + shaderName).c_str()))
    {
        ShaderSelection(
            [&matRef]
            (WeakPtr<Shader> shader)
            {
                matRef.Load(matRef.GetVertexShader(), shader);
            },
            context
        );
    }

    shaderName = "None";
    if(matRef.GetVertexShader().lock())
    {
        WeakPtr<AssetMetaData> shaderMeta = Project::GetActive()->GetEditorAssetManager()->GetMetaData(matRef.GetVertexShader().lock()->id);
        if(shaderMeta.lock())
        {
            shaderName = shaderMeta.lock()->name;
        }
    }

    if(ImGui::Button(("Vertex Shader : " + shaderName).c_str()))
    {
        ShaderSelection(
            [&matRef]
            (WeakPtr<Shader> shader)
            {
                matRef.Load(shader, matRef.GetFragmentShader());
            },
            context
        );
    }


    std::vector<CustomShaderUniformBufferElement>& elements = matRef.GetCustomBufferLayout().GetElements();
    for(auto& element : elements)
    {
        ImGui::Text((element.GetDisplayName() + " : ").c_str());

        switch (element.GetType()) {
            case ShaderElementType::Float:
            {
                // m_shaderProgram->SetFloat(element.GetName(), *(float*)element.GetData());
                break;
            }
            case ShaderElementType::Float2:
            {
                // m_shaderProgram->SetFloat2(element.GetName(), {((float*)element.GetData())[0], ((float*)element.GetData())[1]});
                break;
            }
            case ShaderElementType::Float3:
            {
                // m_shaderProgram->SetFloat3(element.GetName(), {((float*)element.GetData())[0], ((float*)element.GetData())[1], ((float*)element.GetData())[2]});
                break;
            }
            case ShaderElementType::Float4:
            {
                if(!element.HasData())
                {
                    element.SetData(glm::vec4(1));
                }
                glm::vec4& glmColor = *element.GetData<glm::vec4>();
                ImGui::ColorPicker4("##MaterialAlbedoColor", glm::value_ptr(glmColor));
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
                if(!element.HasData())
                {
                    element.SetData<AssetID>(0);
                }

                std::string texName = "None";
                AssetID& texId = *element.GetData<AssetID>();

                WeakPtr<Texture2D> tex;
                ImVec2 uv0{0, 0};
                ImVec2 uv1{1, 1};

                if(texId != EMPTY_ASSET)
                {
                    tex = Project::GetActive()->GetAssetManager()->GetAsset<Texture2D>(texId);

                    WeakPtr<AssetMetaData> texMeta = Project::GetActive()->GetEditorAssetManager()->GetMetaData(texId);
                    if(texMeta.lock())
                    {
                        texName = texMeta.lock()->name;
                    }
                }

                if(!tex.lock())
                {
                    tex = EngineAssetManager::Get().GetAsset("file_icon");
                }
                else
                {
                    uv0 = {1, 1};
                    uv1 = {0, 0};
                }

                if(ImGui::ImageButton(
                        ("Texture : " + texName + "##" + element.GetName()).c_str(),
                        tex.lock()->GetTextureID(),
                        {50, 50},
                        uv0, uv1))
                {
                    TextureSelection(
                        [&matRef, &texId]
                        (WeakPtr<Texture2D> texture)
                        {
                            if(texture.lock())
                            {
                                texId = texture.lock()->id;
                            }
                        },
                        context
                    );
                }
                // m_shaderProgram->SetFloat(element.GetName(), Renderer3D::AddDrawTexture(*tex));
                break;
            }
        }
    }

    // ImGui::Text("Albedo Color : ");
    // glm::vec4 glmAlbedoColor = matRef.GetAlbedoColor();
    // float albedoColor[4] = {glmAlbedoColor.r, glmAlbedoColor.g, glmAlbedoColor.b, glmAlbedoColor.a};
    // ImGui::ColorPicker4("##MaterialAlbedoColor", albedoColor);
    // matRef.SetAlbedoColor({albedoColor[0], albedoColor[1], albedoColor[2], albedoColor[3]});
    //
    // std::string albedoTexName = GetTextureName(matRef.GetAlbedoMap());
    //
    //
    // ImGui::Text("Metallic : ");
    // float metallic = matRef.GetMetallicPercentage();
    // ImGui::SliderFloat("##MaterialMetallicPercentage", &metallic, 0.0f, 1.0f);
    // matRef.SetMetallicPercentage(metallic);
    //
    // std::string metallicTexName = GetTextureName(matRef.GetMetallicMap());
    // if(ImGui::Button(("Metallic Texture : " + metallicTexName ).c_str()))
    // {
    //     TextureSelection(
    //         [&matRef]
    //         (WeakPtr<Texture2D> texture)
    //         {
    //             matRef.SetMetallicTexture(texture);
    //         },
    //         context
    //     );
    // }
    //
    // ImGui::Text("Roughness : ");
    // float roughness = matRef.GetRoughnessPercentage();
    // ImGui::SliderFloat("##MaterialRoughnessPercentage", &roughness, 0.0f, 1.0f);
    // matRef.SetRoughnessPercentage(roughness);
    //
    // std::string roughnessTexName = GetTextureName(matRef.GetRoughnessMap());
    // if(ImGui::Button(("Roughness Texture : " + roughnessTexName).c_str()))
    // {
    //     TextureSelection(
    //         [&matRef]
    //         (WeakPtr<Texture2D> texture)
    //         {
    //             matRef.SetRoughnessMap(texture);
    //         },
    //         context
    //     );
    // }
    //
    // std::string occlusionTexName = GetTextureName(matRef.GetAmbiantOcclusionMap());
    // if(ImGui::Button(("Occlusion Texture : " + occlusionTexName).c_str()))
    // {
    //     TextureSelection(
    //         [&matRef]
    //         (WeakPtr<Texture2D> texture)
    //         {
    //             matRef.SetAmbiantOcclusionMap(texture);
    //         },
    //         context
    //     );
    // }

    if(ImGui::Button("Save"))
    {
        MaterialSerializer::Serialize(*mat.lock(), metaData->path);
    }

    if(ImGui::Button("Delete"))
    {
        Project::GetActive()->GetEditorAssetManager()->DeleteMeta(metaData);
    }

    ImGui::PopStyleVar();
}

void MaterialAssetInspector::TextureSelection(std::function<void(WeakPtr<Texture2D>)> textureSelectedCallback, Application& context)
{
    context.AddLayer<AssetSelectorLayer>(AssetType::TEXTURE2D);
    WeakPtr<AssetSelectorLayer> layer = context.GetLayer<AssetSelectorLayer>();
    if(layer.lock())
    {
        layer.lock()->SetSelectionCallback(
            [textureSelectedCallback](AssetID id)
            {
                textureSelectedCallback(AssetSelectionCheck<Texture2D>(id));
            }
        );
    }
}

void MaterialAssetInspector::ShaderSelection(std::function<void(WeakPtr<Shader>)> shaderSelectedCallback, Application& context)
{
    context.AddLayer<AssetSelectorLayer>(AssetType::SHADER);
    WeakPtr<AssetSelectorLayer> layer = context.GetLayer<AssetSelectorLayer>();
    if(layer.lock())
    {
        layer.lock()->SetSelectionCallback(
            [shaderSelectedCallback](AssetID id)
            {
                shaderSelectedCallback(AssetSelectionCheck<Shader>(id));
            }
        );
    }
}

std::string MaterialAssetInspector::GetTextureName(WeakPtr<Texture2D> texture)
{
    std::string texName = "None";
    if(texture.lock())
    {
        WeakPtr<AssetMetaData> texMeta = Project::GetActive()->GetEditorAssetManager()->GetMetaData(texture.lock()->id);
        if(texMeta.lock())
        {
            texName = texMeta.lock()->name;
        }
    }
    return texName;
}

void Texture2DAssetInspector::Show(SharedPtr<AssetMetaData> metaData, Application& context)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if(!metaData)
    {
        ImGui::Text("Texture2D meta data error");
        return;
    }

    ImGui::Text(("Texture 2D : " + metaData->name).c_str());

    WeakPtr<Texture2D> texture = Project::GetActive()->GetAssetManager()->GetAsset<Texture2D>(metaData->id);
    if(texture.lock())
    {
        ImVec2 region = ImGui::GetContentRegionAvail();
        ImVec2 imageSize = {region.x / 1.2f, 1.0f};
        float textureRatio = (float)texture.lock()->GetHeight() / texture.lock()->GetWidth();
        imageSize.y *= imageSize.x * textureRatio;

        ImGui::Image(texture.lock()->GetTextureID(), imageSize, {1, 1}, {0, 0});

        // ImGui::Text("Texture Filter : ");
        // Texture2D::Filter texFilter = texture.lock()->GetFilter();
        // const char* filterTypes[] = {"Nearest", "Linear"};
        // const char* currentFilter = nullptr;
        //
        // if(ImGui::BeginCombo("##TextureFilter", currentFilter))
        // {
        //     for(const auto& filter : filterTypes)
        //     {
        //         bool isSelected = currentFilter == filter;
        //         if(ImGui::Selectable(filter, isSelected))
        //         {
        //             currentFilter = filter;
        //         }
        //         if(isSelected)
        //         {
        //             ImGui::SetItemDefaultFocus();
        //         }
        //     }
        //
        //     ImGui::EndCombo();
        // }
        //
        // if(ImGui::Button("Apply"))
        // {
        //     texture.lock()->SetFilter(StringToFilter(currentFilter));
        // }
    }

    if(ImGui::Button("Delete"))
    {
        Project::GetActive()->GetEditorAssetManager()->DeleteMeta(metaData);
    }

    ImGui::PopStyleVar();
}

const char* Texture2DAssetInspector::FilterToChar(Texture2D::Filter textureFilter)
{
    switch (textureFilter)
    {
        case Texture2D::Filter::Nearest: return "Nearest";
        case Texture2D::Filter::Linear: return "Linear";
        case Texture2D::Filter::Length: return "Length";
    }
}

Texture2D::Filter Texture2DAssetInspector::StringToFilter(const std::string& value)
{
    if("Nearest" == value)
    {
        return Texture2D::Filter::Nearest;
    }
    if("Linear" == value)
    {
        return Texture2D::Filter::Linear;
    }
    if("Length" == value)
    {
        return Texture2D::Filter::Length;
    }

    return Texture2D::Filter::Nearest;
}

}
