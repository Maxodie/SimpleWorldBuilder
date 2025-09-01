#pragma once

#include "WorldBuilder.hpp"

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

