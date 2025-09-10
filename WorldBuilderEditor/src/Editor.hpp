#pragma once
#include "Core/ECS/Entity.hpp"
#include "Core/Project.hpp"
#include "UIEditor/Inspector/Inspector.hpp"
#include "WorldBuilder.hpp"

#include "UIEditor/ViewportLayer.hpp"
#include "UIEditor/RessourcesLayer/RessourcesLayer.hpp"
#include "UIEditor/CommandLineBarLayer.hpp"
#include "UIEditor/EditorShortCutInputManager.hpp"
#include "UIEditor/Hierarchy/HierarchyLayer.hpp"
#include "UIEditor/MainMenuBarLayer.hpp"

class EditorLayer : public WB::Layer
{
public:
    EditorLayer();

    virtual void Update() override;

    virtual void UpdateGUI() override;

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    void SwitchScene(WB::AssetID sceneID);

private:
    template<typename T>
    T Lerp(const T& a, const T& b, float t)
    {
        return a + t * (b - a);
    }

    template<typename T>
    T Clamp(const T& value, const T& min, const T& max)
    {
        T result = value;
        if(result > max)
        {
            result = max;
        }

        if(result < min)
        {
            result = min;
        }
        return result;
    }

    void CommandLineShortcut();

    void StartProject();
    void OnProjectCreationCanceled();
    void SetupProject();
    void SetupProjectScene();

    void OnEntitySelectedInHierarchy(WB::Entity entity);

    void OnCamForwardPressed(Keycode key);
    void OnCamBackwardPressed(Keycode key);
    void OnStartPlayInEditor(Keycode key);
    void OnEndPlayInEditor(Keycode key);


private:
    WeakPtr<WB::MainMenuBarLayer> m_mainMenuBarLayer;
    WeakPtr<WB::ViewportLayer> m_viewportLayer;
    WeakPtr<WB::CommandLineBarLayer> m_commandBarLayer;
    WeakPtr<WB::RessourcesLayer> m_ressourcesLayer;
    WeakPtr<WB::HierarchyLayer> m_hierarchyLayer;
    WeakPtr<WB::InspectorLayer> m_inspectorLayer;

    WB::InputTable inputTable;

    SharedPtr<WB::Scene3D> m_activeScene;
    WB::Scene3D m_editorScene;

    WB::EditorShortcutInputManager m_shortcutManger;

    bool m_playMode = false;
};
