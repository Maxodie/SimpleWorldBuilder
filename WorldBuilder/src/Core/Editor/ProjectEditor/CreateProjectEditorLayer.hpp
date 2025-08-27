#pragma once
#include "Core/LayerStack.hpp"

namespace WB
{

class CreateProjectEditorLayer : public Layer
{
public:
    CreateProjectEditorLayer();
    ~CreateProjectEditorLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

protected:
    void Close();

private:
    std::string pathBuffer{"C:/"};
    std::string nameBuffer{"New Project"};
};

}
