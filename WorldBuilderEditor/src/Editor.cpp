#include "Editor.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "Core/AssetManager/Importer/ModelImporter.hpp"
#include "Core/Commons/SceneManagement.hpp"
#include "Core/ECS/TransformComponent.hpp"
#include "WorldBuilder.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"
#include "Core/Serializer/AssetManagerSerializer.hpp"
#include "Core/Serializer/SceneSerializer.hpp"
#include "UIEditor/ProjectEditor/OpenProjectEditorLayer.hpp"
#include "UIEditor/ProjectEditor/CreateProjectEditorLayer.hpp"
#include "UIEditor/GuizmoEditor.hpp"

EditorLayer::EditorLayer()
{

}

void EditorLayer::Update()
{
    if(m_viewportLayer.lock() && m_activeScene.lock())
    {
        if(m_playMode)
        {
            m_viewportLayer.lock()->Bind(); //need to bind the other scene when run is started
            m_activeScene.lock()->BeginScene();
            m_activeScene.lock()->UpdateScene();
            m_activeScene.lock()->EndScene();
            m_viewportLayer.lock()->Unbind();
        }
        else
        {
            m_viewportLayer.lock()->Bind();
            m_editorScene.BeginScene();
            m_activeScene.lock()->UpdateScene();
            m_editorScene.EndScene();
            m_viewportLayer.lock()->Unbind();
        }
    }

}

void EditorLayer::UpdateGUI()
{
}

void EditorLayer::OnAttach()
{
    CLIENT_LOG_SUCCESS("Editor attached");

    StartProject();

    //CAMERA EDITOR
    WB::Entity camera = m_editorScene.CreateEntity();
    camera.AddComponent<WB::Camera>();
    camera.AddComponent<WB::TransformComponent>();
    m_editorScene.SetMainCameraEntity(camera);
    ///////////////

    inputTable.BindInput(Keycode::WB_KEY_S, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamBackwardPressed));
    inputTable.BindInput(Keycode::WB_KEY_W, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamForwardPressed));
    inputTable.BindInput(Keycode::WB_KEY_A, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamLeftPressed));
    inputTable.BindInput(Keycode::WB_KEY_D, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamRightPressed));
    inputTable.BindInput(Keycode::WB_KEY_Q, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamrotLeftPressed));
    inputTable.BindInput(Keycode::WB_KEY_E, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnCamrotRightPressed));
    inputTable.BindInput(Keycode::WB_KEY_P, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnStartPlayInEditor));
    inputTable.BindInput(Keycode::WB_KEY_O, InputState::REPEATED, WB_BIND_FUN1(EditorLayer::OnEndPlayInEditor));
    WB::Input::SetInputTable(inputTable);

    //Shortcuts, duh
    m_shortcutManger.BindShortcut(WB_BIND_FUN0(EditorLayer::CommandLineShortcut), WB::Shortcut::Semicolon);
}

void EditorLayer::OnDetach()
{
    CLIENT_LOG_SUCCESS("Editor Detached");
}

void EditorLayer::SwitchScene(WB::AssetID sceneID)
{
    // if(m_activeScene && sceneID == m_activeScene->id)
    // {
    //     return;
    // }

    m_activeScene = WB::SceneManagement::Get().SwitchSceneByAssetID(sceneID);

    // m_activeScene = WB::Project::GetActive()->GetAssetManager()->GetAsset<WB::Scene3D>(sceneID).lock();

    if(m_mainMenuBarLayer.lock())
    {
        m_mainMenuBarLayer.lock()->SetActiveScene(m_activeScene);
    }

    if(m_hierarchyLayer.lock())
    {
        m_hierarchyLayer.lock()->SetActiveScene(m_activeScene);
    }

    if(m_inspectorLayer.lock())
    {
        m_inspectorLayer.lock()->RemoveEntity();
    }
}

void EditorLayer::CommandLineShortcut()
{
    CLIENT_LOG_DEBUG("caca");
}

void EditorLayer::StartProject()
{
    GetContext()->AddLayer<WB::CreateProjectEditorLayer>();
    WeakPtr<WB::CreateProjectEditorLayer> createProject = GetContext()->GetLayer<WB::CreateProjectEditorLayer>();

    WB_CLIENT_ASSERT(createProject.lock(), "could get open project layer");
    createProject.lock()->AddOnProjectCreatedCallback(WB_BIND_FUN0(EditorLayer::SetupProject));//by default it open the project
    createProject.lock()->AddOnCancelCallback(WB_BIND_FUN0(EditorLayer::OnProjectCreationCanceled));//by default it open the project
}

void EditorLayer::OnProjectCreationCanceled()
{
    GetContext()->AddLayer<WB::OpenProjectEditorLayer>(false);
    WeakPtr<WB::OpenProjectEditorLayer> openLayer = GetContext()->GetLayer<WB::OpenProjectEditorLayer>();

    WB_CLIENT_ASSERT(openLayer.lock(), "could get open project layer");
    openLayer.lock()->AddOnProjectOpenedCallback(WB_BIND_FUN0(EditorLayer::SetupProject));
}

void EditorLayer::SetupProject()
{
    SetupProjectScene();

    GetContext()->AddLayer<WB::MainMenuBarLayer>(m_activeScene);
    m_mainMenuBarLayer = GetContext()->GetLayer<WB::MainMenuBarLayer>();

    GetContext()->AddLayer<WB::CommandLineBarLayer>();
    m_commandBarLayer = GetContext()->GetLayer<WB::CommandLineBarLayer>();

    GetContext()->AddLayer<WB::RessourcesLayer>();
    m_ressourcesLayer = GetContext()->GetLayer<WB::RessourcesLayer>();
    m_ressourcesLayer.lock()->SetOnAssetSelectedCallback(WB_BIND_FUN1(EditorLayer::OnAssetSelectedInHierarchy));

    // SCENE
    GetContext()->AddLayer<WB::ViewportLayer>(m_editorScene);
    m_viewportLayer = GetContext()->GetLayer<WB::ViewportLayer>();

    GetContext()->AddLayer<WB::HierarchyLayer>(m_activeScene);
    m_hierarchyLayer = GetContext()->GetLayer<WB::HierarchyLayer>();
    m_hierarchyLayer.lock()->SetOnEntitySelectedCallback(WB_BIND_FUN1(EditorLayer::OnEntitySelectedInHierarchy));

    GetContext()->AddLayer<WB::InspectorLayer>();
    m_inspectorLayer = GetContext()->GetLayer<WB::InspectorLayer>();
}

void EditorLayer::SetupProjectScene()
{
    const WB::Path scenePath = WB::Project::GetActive()->GetSettings().activeScenePath;
    WB::Path metaDataPath = WB::EditorAssetManager::ConvertToMetaPath(scenePath);
    WeakPtr<WB::AssetMetaData> sceneMetaData;

    if(WB::FileSystem::Exists(metaDataPath))
    {
        sceneMetaData = WB::Project::GetActive()->GetEditorAssetManager()->LoadMetaData(metaDataPath);
    }

    if(sceneMetaData.lock())
    {
        SwitchScene(sceneMetaData.lock()->id);
    }
    else
    {
        m_activeScene = WB::Project::GetActive()->GetEditorAssetManager()->CreateAsset<WB::Scene3D>(WB::AssetType::SCENE, scenePath, scenePath.filename().string());

        if(m_activeScene.lock())
        {
            SwitchScene(m_activeScene.lock()->id);
        }
        else
        {
            CORE_LOG_ERROR("Could not create default sample scene");
        }
    }

}

void EditorLayer::OnEntitySelectedInHierarchy(WB::Entity entity)
{
    if(m_inspectorLayer.lock())
    {
        m_inspectorLayer.lock()->SetCurrentEntity(entity);
        GuizmoEditor::OnEntitySelectedInHierarchy(entity);
    }
}

void EditorLayer::OnAssetSelectedInHierarchy(SharedPtr<WB::AssetMetaData> metaData)
{
    if(m_inspectorLayer.lock())
    {
        m_inspectorLayer.lock()->SetCurrentAsset(metaData);
    }
}

void EditorLayer::OnCamLeftPressed(Keycode key)
{
    WB::TransformComponent& camTr = m_editorScene.GetMainCameraEntity().Get<WB::TransformComponent>();
    glm::vec3 base = camTr.GetPosition();
    glm::vec3 left = camTr.GetLeft();
    /**/
    camTr.SetPosition(Lerp(base, base + left, 10 * WB::Application::GetDeltaTime()));
}

void EditorLayer::OnCamRightPressed(Keycode key)
{
    WB::TransformComponent& camTr = m_editorScene.GetMainCameraEntity().Get<WB::TransformComponent>();
    glm::vec3 base = camTr.GetPosition();
    glm::vec3 right = -camTr.GetLeft();
    /**/
    camTr.SetPosition(Lerp(base, base + right, 10 * WB::Application::GetDeltaTime()));
}

void EditorLayer::OnCamForwardPressed(Keycode key)
{
    WB::TransformComponent& camTr = m_editorScene.GetMainCameraEntity().Get<WB::TransformComponent>();
    glm::vec3 base = camTr.GetPosition();
    glm::vec3 forwa = camTr.GetForward();
    /**/
    camTr.SetPosition(Lerp(base, base + forwa, 10 * WB::Application::GetDeltaTime()));
}

void EditorLayer::OnCamBackwardPressed(Keycode key)
{
    WB::TransformComponent& camTr = m_editorScene.GetMainCameraEntity().Get<WB::TransformComponent>();
    glm::vec3 base = camTr.GetPosition();
    glm::vec3 forwa = camTr.GetForward();
    /**/
    camTr.SetPosition(Lerp(base, base - forwa, 10 * WB::Application::GetDeltaTime()));
}

void EditorLayer::OnCamrotLeftPressed(Keycode key)
{
    WB::TransformComponent& camTr = m_editorScene.GetMainCameraEntity().Get<WB::TransformComponent>();
    glm::quat up = glm::quat({0, 1, 0});
    /**/

    // camTr.SetRotation(Lerp(base, base + up, 500 * WB::Application::GetDeltaTime()));
    camTr.Rotate(up);
}

void EditorLayer::OnCamrotRightPressed(Keycode key)
{
    WB::TransformComponent& camTr = m_editorScene.GetMainCameraEntity().Get<WB::TransformComponent>();
    glm::vec3 base = camTr.GetRotation();
    glm::vec3 up = glm::radians(glm::vec3(0, 1, 0));
    /**/

    camTr.SetRotation(Lerp(base, base - up, 500 * WB::Application::GetDeltaTime()));
}

void EditorLayer::OnStartPlayInEditor(Keycode key)
{
    /*m_scene.PrepareScene();*/
}

void EditorLayer::OnEndPlayInEditor(Keycode key)
{
    /*m_scene.RestoreScene();*/
}

extern void OnAppStarted(WB::Application &app)
{
    app.AddLayer<EditorLayer>();
}
