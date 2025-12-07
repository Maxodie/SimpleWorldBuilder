#include "UIEditor/Inspector/ComponentInspector.hpp"
#include "Core/Log/Log.hpp"
#include "UIEditor/GuizmoEditor.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

namespace WB
{

void InfoComponentInspector::Show(InfoComponent& info)
{
    ImGuiTreeNodeFlags treeFlag = ImGuiTreeNodeFlags_DefaultOpen;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if (ImGui::TreeNodeEx("Info Component", treeFlag))
    {
        ImGui::InputText("##info_name", &info.name);

        ImGui::TreePop();
    }
    ImGui::PopStyleVar();
}

void TransformComponentInspector::Show(TransformComponent& tr)
{
    ImGuiTreeNodeFlags treeFlag = ImGuiTreeNodeFlags_DefaultOpen;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if (ImGui::TreeNodeEx("Transform Component", treeFlag))
    {
        float pos[3] = {tr.GetPosition().x, tr.GetPosition().y, tr.GetPosition().z};
        ImGui::DragFloat3("position", pos, 0.01f, -1000.0f, 1000.0f);
        tr.SetPosition({pos[0], pos[1], pos[2]});

        glm::vec3 rot = glm::degrees(tr.GetRotation());
        ImGui::DragFloat3("rotation", glm::value_ptr(rot), 0.1f, -1000.0f, 1000.0f);
        tr.SetRotation(glm::radians(rot));

        float scale[3] = {tr.GetScale().x, tr.GetScale().y, tr.GetScale().z};
        ImGui::DragFloat3("scale", scale, 0.01f, -1000.0f, 1000.0f);
        tr.SetScale({scale[0], scale[1], scale[2]});

        ImGui::TreePop();
    }
    ImGui::PopStyleVar();
}

void ModelComponentInspector::Show(ModelComponent& model, Application& context)
{
    ImGuiTreeNodeFlags treeFlag = ImGuiTreeNodeFlags_DefaultOpen;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if (ImGui::TreeNodeEx("Model Component", treeFlag))
    {
        std::string name = "No model";

        if(model.asset.lock())
        {
            ImGui::Text(("meshes nuVsmber " + std::to_string(model.asset.lock()->meshes.size())).c_str());

            WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(model.asset.lock()->id);
            if(metaData.lock())
            {
                name = metaData.lock()->name;
            }
        }

        if(ImGui::Button(("Model : " + name).c_str()))
        {
            context.AddLayer<AssetSelectorLayer>(AssetType::MODEL);
            WeakPtr<AssetSelectorLayer> layer = context.GetLayer<AssetSelectorLayer>();
            if(layer.lock())
            {
                layer.lock()->SetSelectionCallback(
                    [&](AssetID id)
                    {
                        if(id == EMPTY_ASSET)
                        {
                            model.asset = {};
                        }
                        else
                        {
                            model.asset = Project::GetActive()->GetAssetManager()->GetAsset<ModelAsset>(id);
                        }
                    }
                );
            }
        }

        name = "No material";
        if(model.material.lock())
        {
            WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(model.material.lock()->id);
            if(metaData.lock())
            {
                name = metaData.lock()->name;
            }
        }

        if(ImGui::Button(("Material : " + name).c_str()))
        {
            context.AddLayer<AssetSelectorLayer>(AssetType::MATERIAL);
            WeakPtr<AssetSelectorLayer> layer = context.GetLayer<AssetSelectorLayer>();
            if(layer.lock())
            {
                layer.lock()->SetSelectionCallback(
                    [&](AssetID id)
                    {
                        if(id == EMPTY_ASSET)
                        {
                            model.material = {};
                        }
                        else
                        {
                            model.material = Project::GetActive()->GetAssetManager()->GetAsset<Material>(id);
                        }
                    }
                );
            }
        }


        ImGui::TreePop();
    }
    ImGui::PopStyleVar();
}

void PointLightComponentInspector::Show(PointLightComponent& light, Application& context)
{
    ImGuiTreeNodeFlags treeFlag = ImGuiTreeNodeFlags_DefaultOpen;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    if (ImGui::TreeNodeEx("Point Light Component", treeFlag))
    {
        ImGui::Text("Color : ");
        glm::vec4 glmAlbedoColor = light.GetColor();
        float albedoColor[4] = {glmAlbedoColor.r, glmAlbedoColor.g, glmAlbedoColor.b, glmAlbedoColor.a};
        ImGui::ColorPicker4("##MaterialAlbedoColor", albedoColor);
        light.SetColor({albedoColor[0], albedoColor[1], albedoColor[2], albedoColor[3]});

        ImGui::TreePop();
    }
    ImGui::PopStyleVar();
}

}
