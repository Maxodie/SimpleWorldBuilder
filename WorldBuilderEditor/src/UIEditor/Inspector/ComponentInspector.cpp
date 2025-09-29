#include "UIEditor/Inspector/ComponentInspector.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
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

        float rot[3] = {glm::degrees(tr.GetRotation().x), glm::degrees(tr.GetRotation().y), glm::degrees(tr.GetRotation().z)};
        ImGui::DragFloat3("rotation", rot, 0.1f, -1000.0f, 1000.0f);
        tr.SetRotation({glm::radians(rot[0]), glm::radians(rot[1]), glm::radians(rot[2])});

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
                        model.asset = Project::GetActive()->GetAssetManager()->GetAsset<ModelAsset>(id);
                    }
                );
            }
        }


        ImGui::TreePop();
    }
    ImGui::PopStyleVar();
}

}
