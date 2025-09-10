#include "UIEditor/Inspector/Inspector.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/Log/Log.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
#include "WorldBuilder.hpp"
#include "Core/AssetManager/Importer/ModelImporter.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"

namespace WB
{

void InspectorLayer::Update()
{

}

void InspectorLayer::UpdateGUI()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Inspector");
    ImVec2 hierarchySize = ImGui::GetContentRegionAvail();

    if(m_currentEntity.Exists())
    {
        if(ImGui::BeginChild("Component List"))
        {
            ImGuiTreeNodeFlags treeFlag = ImGuiTreeNodeFlags_DefaultOpen;
            if(m_currentEntity.Has<InfoComponent>())
            {
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                if (ImGui::TreeNodeEx("Info Component", treeFlag))
                {
                    InfoComponent& info = m_currentEntity.Get<InfoComponent>();
                    ImGui::Text(("name : " + info.name).c_str());

                    ImGui::TreePop();
                }
                ImGui::PopStyleVar();
            }

            if(m_currentEntity.Has<TransformComponent>())
            {
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                if (ImGui::TreeNodeEx("Transform Component", treeFlag))
                {
                    TransformComponent& tr = m_currentEntity.Get<TransformComponent>();
                    float pos[3] = {tr.GetPosition().x, tr.GetPosition().y, tr.GetPosition().z};
                    ImGui::DragFloat3("position", pos, 0.1f, -1000.0f, 1000.0f);
                    tr.SetPosition(glm::vec3(pos[0], pos[1], pos[2]));

                    float rot[3] = {glm::degrees(tr.GetRotation().x), glm::degrees(tr.GetRotation().y), glm::degrees(tr.GetRotation().z)};
                    ImGui::DragFloat3("rotation", rot, 0.1f, -1000.0f, 1000.0f);
                    tr.SetRotation(glm::vec3(glm::radians(rot[0]), glm::radians(rot[1]), glm::radians(rot[2])));


                    ImGui::TreePop();
                }
                ImGui::PopStyleVar();
            }

            if(m_currentEntity.Has<ModelComponent>())
            {
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                if (ImGui::TreeNodeEx("Model Component", treeFlag))
                {
                    ModelComponent& model = m_currentEntity.Get<ModelComponent>();
                    if(model.asset.lock())
                    {
                        ImGui::Text(("meshes nuVsmber " + std::to_string(model.asset.lock()->meshes.size())).c_str());
                        if(!model.asset.lock())
                        {
                            CLIENT_LOG_ERROR("model asset not valid");
                        }

                        WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(model.asset.lock()->id);
                        if(metaData.lock())
                        {
                            if(ImGui::Button(("Model : " + metaData.lock()->name).c_str()))
                            {
                                GetContext()->AddLayer<AssetSelectorLayer>(metaData.lock()->type);
                                WeakPtr<AssetSelectorLayer> layer = GetContext()->GetLayer<AssetSelectorLayer>();
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
                        }
                    }


                    ImGui::TreePop();
                }
                ImGui::PopStyleVar();
            }

            if(ImGui::Button("Add Component"))
            {

                GetContext()->AddLayer<AssetSelectorLayer>(AssetType::MODEL);
                WeakPtr<AssetSelectorLayer> layer = GetContext()->GetLayer<AssetSelectorLayer>();

                if(layer.lock())
                {
                    layer.lock()->SetSelectionCallback(
                        [&](AssetID id)
                        {
                            WeakPtr<ModelAsset> asset = Project::GetActive()->GetAssetManager()->GetAsset<ModelAsset>(id);
                            m_currentEntity.AddComponent<ModelComponent>().asset = asset;
                        }
                    );
                }

                TransformComponent& tr = m_currentEntity.AddComponent<TransformComponent>();
                tr.SetScale({0.2f, 0.2f, 0.2f});
                tr.SetPosition({0.0f, 0.0f, 0.8f});
            }

            ImGui::EndChild();
        }


    }


    ImGui::End();
    ImGui::PopStyleVar();
}

void InspectorLayer::OnAttach()
{

}

void InspectorLayer::OnDetach()
{

}

}
