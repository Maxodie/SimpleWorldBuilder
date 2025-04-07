#include "WorldBuilder.hpp"
class EditorLayer : public WB::Layer
{
public:
    EditorLayer() = default;

    virtual void Update() override
    {
        WB::Renderer3D::BeginScene();
        WB::Renderer3D::DrawModel(*model);
        WB::Renderer3D::EndScene();
    }

    virtual void UpdateGUI() override
    {

    }

    virtual void OnAttach() override
    {
        CLIENT_LOG_DEBUG("Editor attached");

        model = WB::MakeShared<WB::Model>(
            WB::Model {
                .m_verticies = {
                    glm::vec3(-0.5f, 0.5f, 0.0f),
                    glm::vec3(0.5f, -0.5f, 0.0f),
                    glm::vec3(0.5f, 0.5f, 0.0f),
                    glm::vec3(0.5f, -0.5f, 0.0f),

                    glm::vec3(-0.5f, 0.5f, -0.5f),
                    glm::vec3(-0.5f, -0.5f, -0.5f),
                    glm::vec3(0.5f, 0.5f, -0.5f),
                    glm::vec3(0.5f, -0.5f, -0.5f),
                },
                .m_indices = {
                    0, 2, 3, 0, 3, 1,
                    2, 6, 7, 2, 7, 3,
                    6, 4, 5, 6, 5, 7,
                    4, 0, 1, 4, 1, 5,
                    0, 4, 6, 0, 6, 2,
                    1, 5, 7, 1, 7, 3,
                }
            }
        );
    }

    virtual void OnDettach() override {CLIENT_LOG_DEBUG("Editor Detached");}

private:
    WB::SharedPtr<WB::Model> model;
};

extern void OnAppStarted(WB::Application &app)
{
    app.AddLayer<EditorLayer>();
}
