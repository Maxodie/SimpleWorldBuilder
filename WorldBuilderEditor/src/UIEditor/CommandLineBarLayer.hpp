#pragma once

#include "WorldBuilder.hpp"

namespace WB
{

class CommandLineBarLayer : public Layer
{
public:
    CommandLineBarLayer();
    virtual ~CommandLineBarLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnInputCallback(Keycode key);

private:
    std::string inputs;
};

}

