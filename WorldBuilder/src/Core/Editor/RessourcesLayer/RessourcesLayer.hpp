#pragma once
#include "Core/LayerStack.hpp"

namespace WB
{

class RessourcesLayer : public Layer
{
public:
    RessourcesLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

private:
    Path m_currentViewPath;
};

}
