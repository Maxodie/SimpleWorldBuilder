#pragma once
#include "Core/LayerStack.hpp"

namespace WB
{

class ProjectList;

class OpenProjectEditorLayer : public Layer
{
public:
    OpenProjectEditorLayer();
    ~OpenProjectEditorLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

protected:
    void Close();

private:
    const ProjectList& m_projectList;
};

}
