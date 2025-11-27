#include "UIEditor/Inspector/AssetInspector.hpp"
#include "Core/Serializer/MaterialSerializer.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
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

    ImGui::Text("Albedo Color : ");
    glm::vec4 glmAlbedoColor = matRef.GetAlbedoColor();
    float albedoColor[4] = {glmAlbedoColor.r, glmAlbedoColor.g, glmAlbedoColor.b, glmAlbedoColor.a};
    ImGui::ColorPicker4("##MaterialAlbedoColor", albedoColor);
    matRef.SetAlbedoColor({albedoColor[0], albedoColor[1], albedoColor[2], albedoColor[3]});

    const WeakPtr<Texture2D>& albedoTex = matRef.GetAlbedoTexture();
    std::string albedoTexName = "None";
    if(albedoTex.lock())
    {
        WeakPtr<AssetMetaData> albedoTexMeta = Project::GetActive()->GetEditorAssetManager()->GetMetaData(albedoTex.lock()->id);
        if(albedoTexMeta.lock())
        {
            albedoTexName = albedoTexMeta.lock()->name;
        }
    }

    if(ImGui::Button(("Albedo Texture : " + albedoTexName).c_str()))
    {
        context.AddLayer<AssetSelectorLayer>(AssetType::TEXTURE2D);
        WeakPtr<AssetSelectorLayer> layer = context.GetLayer<AssetSelectorLayer>();
        if(layer.lock())
        {
            layer.lock()->SetSelectionCallback(
                [&](AssetID id)
                {
                    if(id == EMPTY_ASSET)
                    {
                        matRef.SetTexture({});
                    }
                    else
                    {
                        matRef.SetTexture(Project::GetActive()->GetAssetManager()->GetAsset<Texture2D>(id));
                    }
                }
            );
        }
    }

    if(ImGui::Button("Save"))
    {
        Project::GetActive()->GetEditorAssetManager()->DeleteMeta(metaData);
        MaterialSerializer::Serialize(*mat.lock(), metaData->path);
    }

    if(ImGui::Button("Delete"))
    {
        Project::GetActive()->GetEditorAssetManager()->DeleteMeta(metaData);
    }

    ImGui::PopStyleVar();
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
