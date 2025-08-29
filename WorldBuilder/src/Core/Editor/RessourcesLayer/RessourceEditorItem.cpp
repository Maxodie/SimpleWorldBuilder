#include "Core/Editor/RessourcesLayer/RessourceEditorItem.hpp"
#include "imgui.h"

namespace WB
{

void RessourceEditorItem::Draw()
{
    static bool selected = false;

    ImGui::Selectable("selectable", selected);

    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
    {
        // Do stuff on Selectable() double click.
        selected = !selected;

        Open();
    }
}

void RessourceEditorItem::Open()
{

}

//file
void RessourceEditorFile::Draw()
{

}

//folder
void RessourceEditorFolder::Draw()
{

}

}
