add_executable(WorldBuilder
    WorldBuilder/src/EntryPoint.cpp

        WorldBuilder/src/Core/Core.hpp
        WorldBuilder/src/Core/Application.cpp
        WorldBuilder/src/Core/Application.hpp
        WorldBuilder/src/Core/LayerStack.cpp
        WorldBuilder/src/Core/LayerStack.hpp

            WorldBuilder/src/Core/Log/Log.cpp
            WorldBuilder/src/Core/Log/Log.hpp

            WorldBuilder/src/Core/Event/Event.cpp
            WorldBuilder/src/Core/Event/Event.hpp
)

target_link_libraries(WorldBuilder
    glfw
    glad
)

target_include_directories(WorldBuilder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/src
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/GLFW/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/glad/glad/include
)

set_target_properties(WorldBuilder PROPERTIES
    OUTPUT_NAME WorldBuilder
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_definitions(WorldBuilder PUBLIC
    WB_LOGGER
    WB_ASSERT
)

target_compile_options(WorldBuilder PRIVATE
    -std=c++23
    -g
)
