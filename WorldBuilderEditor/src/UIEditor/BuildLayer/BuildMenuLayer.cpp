#include "UIEditor/BuildLayer/BuildMenuLayer.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/Project.hpp"
#include "UIEditor/RessourcesLayer/AssetSelectorLayer.hpp"
#include "WorldBuilder.hpp"
#include "Core/Commons/SceneManagement.hpp"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

namespace WB
{

BuildMenuLayer::BuildMenuLayer()
    : Layer()
{
}

BuildMenuLayer::~BuildMenuLayer()
{

}

void BuildMenuLayer::Update()
{

}

void BuildMenuLayer::UpdateGUI()
{
    // ImGui::OpenPopup("new_project_popup", ImGuiPopupFlags_MouseButtonRight);

    if (ImGui::Begin("Build Settings", &m_isOpen, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse))
    {
        ImGui::Text("Scene to build");

        SceneBuildRegistry& registry = SceneManagement::Get().GetRegistry();
        for(int i = 0; i < registry.sceneIDs.size(); i++)
        {
            std::string name{"Error, invalid scene"};
            WeakPtr<AssetMetaData> metaData = Project::GetActive()->GetEditorAssetManager()->GetMetaData(registry.sceneIDs[i]);
            if(metaData.lock())
            {
                name = metaData.lock()->name;
            }
            else
            {
                name = "Error";
            }

            ImGui::Text((name + " id : " + std::to_string(i)).c_str());
            ImGui::SameLine();

            if(ImGui::Button(("delete##%d" + std::to_string(i)).c_str()))
            {
                SceneManagement::Get().GetRegistry().RemoveScene(i);
            }
        }

        if(ImGui::Button("Add scene"))
        {
            WeakPtr<AssetSelectorLayer> layer = GetContext()->AddLayer<AssetSelectorLayer>(AssetType::SCENE);
            if(layer.lock())
            {
                layer.lock()->SetSelectionCallback(
                    [&](auto assetID)
                    {
                        SceneManagement::Get().GetRegistry().AddScene(assetID);
                    }
                );
            }
        }

        if (ImGui::Button("Cancel"))
        {
            Close();
        }

        ImGui::End();
    }
}

void BuildMenuLayer::OnAttach()
{
    CORE_LOG_SUCCESS("Create project editor attached");
}

void BuildMenuLayer::OnDetach()
{
    CORE_LOG_SUCCESS("Create project editor detached");
}

void BuildMenuLayer::Close()
{
    ImGui::CloseCurrentPopup();

    GetContext()->RemoveLayer<BuildMenuLayer>();
}

}
