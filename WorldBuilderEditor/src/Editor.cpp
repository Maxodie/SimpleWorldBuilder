#include "Core/Log/Log.hpp"
#include "WorldBuilder.hpp"
#include "WorldBuilderEditor.hpp"

class EditorLayer : public WB::Layer
{
public:
    EditorLayer(WB::Application& app)
        : m_context(app)
    {

    }

    float time = 0.0f;
    virtual void Update() override
    {
        m_frameBuffer->Bind();

        scene.BeginScene();

        tr.Rotate({WB::Application::GetDeltaTime(), WB::Application::GetDeltaTime(), 0.0f});
        tr.UpdateModelMatrix();
        if (tr.GetRotation().y > 360.0f)
        {
            tr.SetRotation(glm::vec3(0.0f));
        }

        WB::Renderer3D::DrawModel(*model, tr);
        scene.UpdateScene();
        scene.EndScene();

        m_frameBuffer->Unbind();
    }

    virtual void UpdateGUI() override
    {
    }

    virtual void OnAttach() override
    {
        CLIENT_LOG_SUCCESS("Editor attached");
        m_frameBuffer = WB::FrameBuffer::Create();

        InitImGUI();

        //setup project
        project = MakeShared<WB::Project>();
        WB::ProjectSettings projectSettings{
            .projectName = "test",
            .projectPath = std::filesystem::current_path(),
            .projectAssetPath = std::filesystem::current_path() / "WorldBuilderEditor/assets"
        };
        project->SetSettings(projectSettings);


        WB::Model newMod;
        newMod.Load("WorldBuilderEditor/assets/monkey.fbx");

        tr.SetScale({0.2f, 0.2f, 0.2f});
        tr.SetPosition({0.0f, 0.0f, 0.8f});

        model = MakeShared<WB::Model>(newMod);

        m_cam.SetupProjectionMatrix(80.f, 800.0f/640.0f, 0.1f, 100.f);
        camTr.SetScale({1.0f, 1.0f, 1.0f});
        camTr.SetPosition({0.0f, 0.0f, 0.0f});
        m_cam.UpdateViewMatrix(camTr);

        inputTable.BindInput(Keycode::WB_KEY_S, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamBackwardPressed));
        inputTable.BindInput(Keycode::WB_KEY_W, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamForwardPressed));
        inputTable.BindInput(Keycode::WB_KEY_P, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnStartPlayInEditor));
        inputTable.BindInput(Keycode::WB_KEY_O, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnEndPlayInEditor));
        WB::Input::SetInputTable(inputTable);

        //Scene data
        m_sceneData.cam = &m_cam;
        m_sceneData.transforms.push_back(&camTr);
        m_sceneData.transforms.push_back(&tr);
        scene.SetData(m_sceneData);

        //Shortcuts, duh
        m_shortcutManger.BindShortcut(WB_BIND_FUN0(EditorLayer::CommandLineShortcut), WB::Shortcut::Semicolon);
    }

    virtual void OnDetach() override
    {
        CLIENT_LOG_SUCCESS("Editor Detached");
    }

private:
    template<typename T>
    T Lerp(const T& a, const T& b, float t)
    {
        return a + t * (b - a);
    }

    template<typename T>
    T Clamp(const T& value, const T& min, const T& max)
    {
        T result = value;
        if(result > max)
        {
            result = max;
        }

        if(result < min)
        {
            result = min;
        }
        return result;
    }
    void CommandLineShortcut() {
        CLIENT_LOG_DEBUG("caca");
    }

    void InitImGUI()
    {
        m_mainMenuBarLayer = m_context.AddLayer<WB::MainMenuBarLayer>();
        m_commandBarLayer = m_context.AddLayer<WB::CommandLineBarLayer>();
        m_viewportLayer = m_context.AddLayer<WB::ViewportLayer>(m_cam, m_frameBuffer);
    }

    void OnCamForwardPressed(Keycode key)
    {
        glm::vec3 base = camTr.GetPosition();
        glm::vec3 forwa = camTr.GetForward();

        camTr.SetPosition(Lerp(base, base + forwa, 10 * WB::Application::GetDeltaTime()));

        m_cam.UpdateViewMatrix(camTr);
    }

    void OnCamBackwardPressed(Keycode key)
    {
        glm::vec3 base = camTr.GetPosition();
        glm::vec3 forwa = camTr.GetForward();

        camTr.SetPosition(Lerp(base, base - forwa, 10 * WB::Application::GetDeltaTime()));

        m_cam.UpdateViewMatrix(camTr);
    }

    void OnStartPlayInEditor(Keycode key)
    {
        scene.PrepareScene();
    }

    void OnEndPlayInEditor(Keycode key)
    {
        scene.RestoreScene();
    }

private:
    WB::Application& m_context;
    SharedPtr<WB::MainMenuBarLayer> m_mainMenuBarLayer;
    SharedPtr<WB::ViewportLayer> m_viewportLayer;
    SharedPtr<WB::CommandLineBarLayer> m_commandBarLayer;

    SharedPtr<WB::Model> model;
    WB::TransformComponent tr;
    WB::TransformComponent camTr;
    WB::Camera m_cam;

    SharedPtr<WB::FrameBuffer> m_frameBuffer;

    WB::InputTable inputTable;

    WB::Scene3D scene;
    WB::SceneData m_sceneData;

    SharedPtr<WB::Project> project;

    WB::EditorShortcutInputManager m_shortcutManger;
};

extern void OnAppStarted(WB::Application &app)
{
    app.AddLayer<EditorLayer>(app);
}
