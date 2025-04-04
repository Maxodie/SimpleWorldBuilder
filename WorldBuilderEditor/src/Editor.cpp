#include "WorldBuilder.hpp"

class EditorLayer : public WB::Layer
{
public:
    EditorLayer() = default;
    virtual void Update() override
    {
        WB::Renderer3D::DrawModel(*model);
    }

    virtual void UpdateGUI() override
    {

    }

    virtual void OnAttach() override { CLIENT_LOG_DEBUG("Editor attached"); }
    virtual void OnDettach() override {CLIENT_LOG_DEBUG("Editor Dettached");}

private:
    WB::SharedPtr<WB::Model> model = WB::MakeShared<WB::Model>(WB::Model());
};

extern void OnAppStarted(WB::Application &app)
{
    app.AddLayer<EditorLayer>();
}
