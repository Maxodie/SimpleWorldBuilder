#include "UIEditor/Inspector/AssetInspector.hpp"
#include "imgui.h"

namespace WB
{

void SceneAssetInspector::Show(SharedPtr<AssetMetaData> metaData)
{
    if(!metaData)
    {
        return;
    }


    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::Text(("Scene : " + metaData->name).c_str());

    if(ImGui::Button("Delete"))
    {
        Project::GetActive()->GetEditorAssetManager()->DeleteMeta(metaData);
        Project::GetActive()->GetAssetManager()->CheckPackagesValidity();
    }

    ImGui::PopStyleVar();
}

}
