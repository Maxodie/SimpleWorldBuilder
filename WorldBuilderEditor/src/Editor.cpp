#include "WorldBuilder.hpp"

class EditorLayer : public WB::Layer
{
public:

    virtual void Update() override
    {
        WB::Renderer3D::BeginScene();
        WB::Renderer3D::DrawModel(*model, tr);
        WB::Renderer3D::EndScene();
    }

    virtual void UpdateGUI() override
    {

    }

    virtual void OnAttach() override
    {
        CLIENT_LOG_DEBUG("Editor attached");
        WB::Model newMod{
                .m_indices = {
                    0, 2, 3, 0, 3, 1,
                    2, 6, 7, 2, 7, 3,
                    6, 4, 5, 6, 5, 7,
                    4, 0, 1, 4, 1, 5,
                    0, 4, 6, 0, 6, 2,
                    1, 5, 7, 1, 7, 3,
                }
            };
        newMod.m_verticies.emplace_back(glm::vec4(0.2f, 0.5f, 0.8f, 1.0f), glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) );
        newMod.m_verticies.emplace_back(glm::vec4(0.3f, 0.5f, 0.7f, 1.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) );
        newMod.m_verticies.emplace_back(glm::vec4(0.4f, 0.5f, 0.6f, 1.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) );
        newMod.m_verticies.emplace_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) );

        newMod.m_verticies.emplace_back(glm::vec4(0.4f, 0.5f, 0.5f, 1.0f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f) );
        newMod.m_verticies.emplace_back(glm::vec4(0.3f, 0.5f, 0.6f, 1.0f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f) );
        newMod.m_verticies.emplace_back(glm::vec4(0.2f, 0.5f, 0.7f, 1.0f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f) );
        newMod.m_verticies.emplace_back(glm::vec4(0.1f, 0.5f, 0.8f, 1.0f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f) );

        model = WB::MakeShared<WB::Model>(newMod);
    }

    virtual void OnDettach() override {CLIENT_LOG_DEBUG("Editor Detached");}

private:
    WB::SharedPtr<WB::Model> model;
    WB::TransformComponent tr;
};

extern void OnAppStarted(WB::Application &app)
{
    app.AddLayer<EditorLayer>();
}
