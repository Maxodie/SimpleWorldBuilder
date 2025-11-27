#include "UIEditor/Inspector/Inspector.hpp"
#include "Core/Log/Log.hpp"
#include "UIEditor/Inspector/AssetInspector.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/AssetManager/EditorAssetManager.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "UIEditor/Inspector/ComponentInspector.hpp"
#include "UIEditor/Inspector/ComponentSelectionLayer.hpp"
#include "WorldBuilder.hpp"
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
                InfoComponentInspector::Show(m_currentEntity.Get<InfoComponent>());
            }

            if(m_currentEntity.Has<TransformComponent>())
            {
                TransformComponentInspector::Show(m_currentEntity.Get<TransformComponent>());
            }

            if(m_currentEntity.Has<ModelComponent>())
            {
                ModelComponentInspector::Show(m_currentEntity.Get<ModelComponent>(), *GetContext());
            }

            if(ImGui::Button("Add Component"))
            {
                GetContext()->AddLayer<ComponentSelectorLayer>();
                WeakPtr<ComponentSelectorLayer> layer = GetContext()->GetLayer<ComponentSelectorLayer>();
                if(layer.lock())
                {
                    layer.lock()->SetSelectionCallback(
                        [&](TypeID id)
                        {
                            if(id == GetTypeID<ModelComponent>())
                            {
                                m_currentEntity.AddComponent<ModelComponent>();
                                m_currentEntity.AddComponent<TransformComponent>();
                                //create default model
                            }
                        }
                    );
                }

            }

            if(ImGui::Button("Destroy"))
            {
                m_currentEntity.Destroy();
            }

            ImGui::EndChild();
        }


    }
    else if(m_metaData)
    {
        //show scene datas
        switch(m_metaData->type)
        {
            case AssetType::SCENE:
            {
                SceneAssetInspector::Show(m_metaData);
                break;
            }
            case AssetType::FOLDER:
                {

                    break;
                }
            case AssetType::MATERIAL:
            {
                MaterialAssetInspector::Show(m_metaData, *GetContext());
                break;
            }
            break;
            case AssetType::MODEL:
            break;
            case AssetType::SHADER:
            break;
            case AssetType::TEXTURE2D:
            {
                Texture2DAssetInspector::Show(m_metaData, *GetContext());
                break;
            }
            case AssetType::UNKNOWN:
            break;
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
