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

private:
    WeakPtr<Scene3D> m_activeScene;
};

}

