#pragma once

#include "Core/LayerStack.hpp"

namespace WB
{

class MainMenuBarLayer : public Layer
{
public:
    MainMenuBarLayer();
    ~MainMenuBarLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

private:
    bool m_isNewFolderDialogOpen = false;
    std::string pathBuffer{"C:/"};
    std::string nameBuffer{"New Project"};
};

}

