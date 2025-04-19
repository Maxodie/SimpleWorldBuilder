#include "Core/Log/Log.hpp"
#include "WorldBuilder.hpp"

class EditorLayer : public WB::Layer
{
public:

    virtual void Update() override
    {
        /*frameBuffer->Bind();*/

        WB::RenderCommand::Clear();

        WB::Renderer3D::BeginScene(cam);

        tr.Rotate({0.001f, 0.001f, 0.0f});
        tr.UpdateModelMatrix();
        if (tr.GetRotation().y > 360.0f)
        {
            tr.SetRotation(glm::vec3(0.0f));
        }

        WB::Renderer3D::DrawModel(*model, tr);
        WB::Renderer3D::EndScene();

        /*frameBuffer->Unbind();*/
    }

    virtual void UpdateGUI() override
    {

    }

    virtual void OnAttach() override
    {
        CLIENT_LOG_DEBUG("Editor attached");
        WB::Model newMod;
        newMod.Load("WorldBuilderEditor/assets/monkey.fbx");

        tr.SetScale({0.2f, 0.2f, 0.2f});
        tr.SetPosition({0.0f, 0.0f, 0.8f});

        model = WB::MakeShared<WB::Model>(newMod);

        cam.UpdateViewProjectionMatrix(80.f, 800.0f/640.0f, 0.1f, 100.f);
        /*frameBuffer = WB::FrameBuffer::Create();*/
        /*frameBuffer->Resize(800.0f, 640.0f);*/

        inputTable.BindInput(Keycode::WB_KEY_S, InputState::REPEATED, WB_BIND_FUN0(EditorLayer::OnCamForwardPressed));
        inputTable.BindInput(Keycode::WB_KEY_S, InputState::RELEASED, WB_BIND_FUN0(EditorLayer::OnCamForwardReleased));
        WB::Input::SetInputTable(inputTable);
    }

    virtual void OnDettach() override {CLIENT_LOG_DEBUG("Editor Detached");}

private:
    void OnCamForwardPressed()
    {
        CLIENT_LOG_DEBUG("Forward presssed");
    }

    void OnCamForwardReleased()
    {
        CLIENT_LOG_DEBUG("Forward released");
    }

private:
    WB::SharedPtr<WB::Model> model;
    WB::TransformComponent tr;
    WB::Camera cam;
    /*WB::SharedPtr<WB::FrameBuffer> frameBuffer;*/
    WB::InputTable inputTable;
};

extern void OnAppStarted(WB::Application &app)
{
    app.AddLayer<EditorLayer>();
}
