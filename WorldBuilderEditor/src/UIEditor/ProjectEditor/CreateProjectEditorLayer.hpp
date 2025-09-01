#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class CreateProjectEditorLayer : public Layer
{
    using ProjectCreatedCallback = std::function<void()>;

public:
    CreateProjectEditorLayer();
    ~CreateProjectEditorLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void AddOnProjectCreatedCallback(const ProjectCreatedCallback&& fun);
    void AddOnCancelCallback(const ProjectCreatedCallback&& fun);

protected:
    void Close();

private:
    std::string pathBuffer{"C:/"};
    std::string nameBuffer{"New Project"};
    std::vector<ProjectCreatedCallback> m_projectCreatedCallbacks;
    std::vector<ProjectCreatedCallback> m_projectCancelCallbacks;
};

}
