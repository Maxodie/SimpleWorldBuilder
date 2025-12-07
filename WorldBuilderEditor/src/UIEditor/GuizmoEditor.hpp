#pragma once

#include "Core/Commons/Scene.hpp"
#include "imgui.h"
#include "ImGuizmo.h"
#include "WorldBuilder.hpp"

class GuizmoEditor
{
public:
    enum class Type : uint16_t
    {
        Translate = ImGuizmo::OPERATION::TRANSLATE,
        Rotate = ImGuizmo::OPERATION::ROTATE,
        Scale = ImGuizmo::OPERATION::SCALE
    };

    enum class Space : uint8_t
    {
        Local = ImGuizmo::MODE::LOCAL,
        World = ImGuizmo::MODE::WORLD
    };

    static void Update(WB::Scene3D& context);
    static void OnEntitySelectedInHierarchy(WB::Entity& entity);

    static void SetGuizmoType(Type type);
    static void SetGuizmoSpace(Space space);

private:
    WB_INLINE static WB::Entity s_selectedEntity;
    WB_INLINE static Type s_guizmoType = Type::Translate;
    WB_INLINE static Space s_guizmoSpace = Space::Local;
};
