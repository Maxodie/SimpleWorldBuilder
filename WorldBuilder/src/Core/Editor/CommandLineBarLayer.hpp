#pragma once

#include "Core/Input/Keycode.hpp"
#include "Core/LayerStack.hpp"

namespace WB
{

class CommandLineBarLayer : public Layer
{
public:
    CommandLineBarLayer();
    ~CommandLineBarLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnInputCallback(Keycode key);

private:
    std::string inputs;
};

}

