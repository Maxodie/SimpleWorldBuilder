add_library(WorldBuilder
    WorldBuilder/src/WorldBuilder.hpp

        WorldBuilder/src/Core/Core.hpp
        WorldBuilder/src/Core/EntryPoint.cpp
        WorldBuilder/src/Core/Application.cpp
        WorldBuilder/src/Core/Application.hpp
        WorldBuilder/src/Core/LayerStack.cpp
        WorldBuilder/src/Core/LayerStack.hpp
            WorldBuilder/src/Core/Log/Log.cpp
            WorldBuilder/src/Core/Log/Log.hpp
            WorldBuilder/src/Core/Event/Event.cpp
            WorldBuilder/src/Core/Event/Event.hpp
            WorldBuilder/src/Core/Window/Window.cpp
            WorldBuilder/src/Core/Window/Window.hpp
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
            WorldBuilder/src/Core/Renderer/VertexBuffer.cpp
            WorldBuilder/src/Core/Renderer/VertexBuffer.hpp

        WorldBuilder/src/Platform/Window/GLFW/GLFWWindow.cpp
        WorldBuilder/src/Platform/Window/GLFW/GLFWWindow.hpp

        WorldBuilder/src/Platform/Renderer/Opengl/OpenglRendererAPI.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglRendererAPI.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglVertexBuffer.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglVertexBuffer.hpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.cpp
        WorldBuilder/src/Platform/Renderer/Opengl/OpenglGLFWGraphicsContext.hpp
)

target_link_libraries(WorldBuilder PRIVATE
    glfw
    glad
    glm_math
    TARGET_MODEL_LOADER
)

target_include_directories(WorldBuilder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/src
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/GLFW/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/glad/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/assimp/assimp/include
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

target_compile_options(WorldBuilder PRIVATE
    -std=c++23
    -g
)
