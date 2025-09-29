#pragma once

#include "WorldBuilder.hpp"

namespace WB
{

class MainMenuBarLayer : public Layer
{
public:
    MainMenuBarLayer(WeakPtr<Scene3D> activeScene);
    virtual ~MainMenuBarLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    WB_INLINE void SetActiveScene(WeakPtr<Scene3D> activeScene) { m_activeScene = activeScene; }

private:
    WeakPtr<Scene3D> m_activeScene;
};

}

