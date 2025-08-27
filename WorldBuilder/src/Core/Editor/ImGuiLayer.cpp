#include "Core/Editor/ImGuiLayer.hpp"
#include "Core/Application.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace WB {

bool ImGuiLayerBase::m_open = false;

void ImGuiLayerBase::BaseInit() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;              // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport /
                                                      // Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform
    // windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    const Application &app = Application::Get();
    GLFWwindow *window =
      static_cast<GLFWwindow *>(app.GetMainWindow()->GetNative());

    // setup render/platform bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    CORE_LOG_SUCCESS("ImGui Initialized");
}

void ImGuiLayerBase::BaseShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    CORE_LOG_SUCCESS("ImGui Shutdown");
}

void ImGuiLayerBase::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window
    // not dockable into, because it would be confusing to have two docking
    // targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |=
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    } else {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render
    // our background and handle the pass-thru hole, so we ask Begin() to not
    // render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window
    // is collapsed). This is because we want to keep our DockSpace() active. If a
    // DockSpace() is inactive, all active windows docked into it will lose their
    // parent and become undocked. We cannot preserve the docking relationship
    // between an active window and an inactive docking, otherwise any change of
    // dockspace/settings would lead to windows being stuck in limbo and never
    // being visible.
    if (!opt_padding)
    {
        /*ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, MenuBarSize()));*/
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    }
    ImGui::Begin("DockSpace", &m_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("First DockSpace");
        ImVec2 content_avail{ImGui::GetContentRegionAvail()};
        ImVec2 size{content_avail.x, content_avail.y - MenuBarSize()};
        size.x = fmax(size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
        size.y = fmax(size.y, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)

        ImGui::DockSpace(dockspace_id, size, dockspace_flags);
    }
    else
    {
        ImGuiIO &io = ImGui::GetIO();
        ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
        ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your "
                    "code, or ");
        ImGui::SameLine(0.0f, 0.0f);
        if (ImGui::SmallButton("click here"))
        {
          io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        }
    }
}

void ImGuiLayerBase::End()
{
    ImGui::End();
    ImGuiIO &io = ImGui::GetIO();
    /*const Application &app = Application::Get();*/
    /*io.DisplaySize = ImVec2((float)app.GetMainWindow()->GetData().w,*/
    /*                        (float)app.GetMainWindow()->GetData().h);*/

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

} // namespace WB
