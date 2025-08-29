#pragma once

#include "Core/Input/InputData.hpp"
#include "Core/LayerStack.hpp"

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

    void OnInputCallback(InputData inputData);

private:
    std::string inputs;
};

}

