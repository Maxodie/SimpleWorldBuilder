add_library(WorldBuilder
    WorldBuilder/src/WorldBuilder.hpp
    WorldBuilder/src/WorldBuilderEditor.hpp

        WorldBuilder/src/Core/Core.hpp
        WorldBuilder/src/Core/EntryPoint.cpp
        WorldBuilder/src/Core/Application.cpp
        WorldBuilder/src/Core/Application.hpp
        WorldBuilder/src/Core/LayerStack.cpp
        WorldBuilder/src/Core/LayerStack.hpp
        WorldBuilder/src/Core/Project.hpp
            WorldBuilder/src/Core/AssetManager/Asset.hpp
            WorldBuilder/src/Core/AssetManager/AssetManagerBase.cpp
            WorldBuilder/src/Core/AssetManager/RuntimeAssetManager.cpp
            WorldBuilder/src/Core/AssetManager/RuntimeAssetManager.hpp
            WorldBuilder/src/Core/AssetManager/EditorAssetManager.cpp
            WorldBuilder/src/Core/AssetManager/EditorAssetManager.hpp
            WorldBuilder/src/Core/Commons/Camera.cpp
            WorldBuilder/src/Core/Commons/Camera.hpp
            WorldBuilder/src/Core/Commons/Scene.cpp
            WorldBuilder/src/Core/Commons/Scene.hpp
            WorldBuilder/src/Core/Commons/Timestep.cpp
            WorldBuilder/src/Core/Commons/Timestep.hpp
            WorldBuilder/src/Core/Editor/ImGuiAdditionals.cpp
            WorldBuilder/src/Core/Editor/ImGuiAdditionals.hpp
            WorldBuilder/src/Core/Editor/ImGuiLayer.cpp
            WorldBuilder/src/Core/Editor/ImGuiLayer.hpp
            WorldBuilder/src/Core/Editor/MainMenuBarLayer.cpp
            WorldBuilder/src/Core/Editor/MainMenuBarLayer.hpp
            WorldBuilder/src/Core/Editor/ViewportLayer.cpp
            WorldBuilder/src/Core/Editor/ViewportLayer.hpp
            WorldBuilder/src/Core/Editor/CommandLineBarLayer.cpp
            WorldBuilder/src/Core/Editor/CommandLineBarLayer.hpp
            WorldBuilder/src/Core/ECS/EcsComponent.hpp
            WorldBuilder/src/Core/Event/Event.cpp
            WorldBuilder/src/Core/Event/Event.hpp
            WorldBuilder/src/Core/Input/Input.cpp
            WorldBuilder/src/Core/Input/Input.hpp
            WorldBuilder/src/Core/Input/Keycode.hpp
            WorldBuilder/src/Core/Log/Log.cpp
            WorldBuilder/src/Core/Log/Log.hpp
            WorldBuilder/src/Core/Renderer/Renderer.cpp
            WorldBuilder/src/Core/Renderer/Renderer.hpp
            WorldBuilder/src/Core/Renderer/RendererAPI.cpp
            WorldBuilder/src/Core/Renderer/RendererAPI.hpp
            WorldBuilder/src/Core/Renderer/Renderer3D.cpp
            WorldBuilder/src/Core/Renderer/Renderer3D.hpp
            WorldBuilder/src/Core/Renderer/GraphicsContext.cpp
            WorldBuilder/src/Core/Renderer/GraphicsContext.hpp
            WorldBuilder/src/Core/Renderer/RenderCommand.cpp
            WorldBuilder/src/Core/Renderer/RenderCommand.hpp
            WorldBuilder/src/Core/Renderer/Buffer.cpp
            WorldBuilder/src/Core/Renderer/Buffer.hpp
            WorldBuilder/src/Core/Renderer/Shader.cpp
            WorldBuilder/src/Core/Renderer/Shader.hpp
            WorldBuilder/src/Core/Renderer/Vertex.cpp
            WorldBuilder/src/Core/Renderer/Vertex.hpp
            WorldBuilder/src/Core/Renderer/Model.cpp
            WorldBuilder/src/Core/Renderer/Model.hpp
            WorldBuilder/src/Core/Renderer/ShaderProgram.cpp
            WorldBuilder/src/Core/Renderer/ShaderProgram.hpp
            WorldBuilder/src/Core/Renderer/FrameBuffer.cpp
            WorldBuilder/src/Core/Renderer/FrameBuffer.hpp
            WorldBuilder/src/Core/Serializer/Serializer.cpp
            WorldBuilder/src/Core/Serializer/Serializer.hpp
            WorldBuilder/src/Core/Serializer/ProjectSerializer.cpp
            WorldBuilder/src/Core/Serializer/ProjectSerializer.hpp
            WorldBuilder/src/Core/Utils/FileSystem.cpp
            WorldBuilder/src/Core/Utils/FileSystem.hpp
            WorldBuilder/src/Core/Window/Window.cpp
            WorldBuilder/src/Core/Window/Window.hpp

        WorldBuilder/src/Platform/Window/GLFW/GLFWWindow.cpp
        WorldBuilder/src/Platform/Window/GLFW/GLFWWindow.hpp
        WorldBuilder/src/Platform/Window/GLFW/GLFWInput.cpp
        WorldBuilder/src/Platform/Window/GLFW/GLFWInput.hpp

        WorldBuilder/src/Platform/Renderer/Opengl/OpenglRendererAPI.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglRendererAPI.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglBuffer.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglBuffer.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglShader.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglShader.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglShaderProgram.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglShaderProgram.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglVertexArrayBuffer.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglVertexArrayBuffer.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglFrameBuffer.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglFrameBuffer.hpp
)

target_link_libraries(WorldBuilder PRIVATE
    glfw
    glad
    glm_math
    TARGET_MODEL_LOADER
    EnTT::EnTT
    imgui
    yaml-cpp::yaml-cpp
)

target_include_directories(WorldBuilder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/src
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/GLFW/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/glad/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/assimp/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/entt/entt/src
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/imgui/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/yamlcpp/yamlcpp/include
)

set_target_properties(WorldBuilder PROPERTIES
    OUTPUT_NAME WorldBuilder
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilder
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilder
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilder
)

target_compile_definitions(WorldBuilder PRIVATE
    WB_LOGGER
    WB_ASSERT
)
