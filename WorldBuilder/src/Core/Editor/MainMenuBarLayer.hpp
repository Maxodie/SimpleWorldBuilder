#pragma once

#include "Core/LayerStack.hpp"

namespace WB
{

class MainMenuBarLayer : public Layer
{
public:
    MainMenuBarLayer();
    virtual ~MainMenuBarLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
};

}

