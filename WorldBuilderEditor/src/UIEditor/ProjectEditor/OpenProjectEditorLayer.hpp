#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class ProjectList;

class OpenProjectEditorLayer : public Layer
{
    using ProjectOpenedCallback = std::function<void()>;

public:
    OpenProjectEditorLayer(bool canCancel = true);
    ~OpenProjectEditorLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void AddOnProjectOpenedCallback(const ProjectOpenedCallback&& fun);

protected:
    void Close();

private:
    std::string pathBuffer{"C:/"};
    const ProjectList& m_projectList;
    std::vector<ProjectOpenedCallback> m_projectOpenedCallbacks;

    bool m_canCancel;
};

}
