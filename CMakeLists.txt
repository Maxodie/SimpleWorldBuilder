cmake_minimum_required(VERSION 3.30)
project(WorldBuilder VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

option(CMAKE_EXPORT_COMPILE_COMMANDS "allow the creatation of an compile_commands.json file" ON)
option(GIT_SUBMODULE "allow git submodule auto update" ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    message("==== create .clang file to store 'CompilationDatabase: build/' ====")
    file(WRITE ".clang"
        "CompileFlags:
            CompilationDatabase: build/"
    )
endif()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND "${GIT_EXECUTABLE} submodule update --init --recursive"
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMAND_ECHO STDOUT)
    endif()
endif()

set(BIN_OUTPUT_DIR "/bin/${CMAKE_SYSTEM_NAME}")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}${BIN_OUTPUT_DIR}")

include(WorldBuilder/SimpleWorldBuilder.cmake)
include(WorldBuilderEditor/WorldBuilderEditor.cmake)
include(WorldBuilderGame/WorldBuilderGame.cmake)
include(WorldBuilder/vendors/GLFW/GLFW.cmake)
include(WorldBuilder/vendors/glad/glad.cmake)
include(WorldBuilder/vendors/glm/glm.cmake)
include(WorldBuilder/vendors/assimp/assimp.cmake)
add_subdirectory(WorldBuilder/vendors/entt/entt)
add_subdirectory(WorldBuilder/vendors/yamlcpp/yamlcpp)
include(WorldBuilder/vendors/imgui/imgui.cmake)
