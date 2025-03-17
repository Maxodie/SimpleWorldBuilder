cmake_minimum_required(VERSION 3.30)
project(WorldBuilder VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    message("==== create .clang file to store 'CompilationDatabase: build/' ====")
    file(WRITE ".clang"
        "CompileFlags:
            CompilationDatabase: build/"
    )
endif()

set(BIN_OUTPUT_DIR "/bin/${CMAKE_SYSTEM_NAME}")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}${BIN_OUTPUT_DIR}")

add_executable(WorldBuilder
    WorldBuilder/src/EntryPoint.cpp
    WorldBuilder/src/Core/Core.hpp

    WorldBuilder/src/Core/Log/Log.cpp
    WorldBuilder/src/Core/Log/Log.hpp

    WorldBuilder/src/Core/Application.cpp
    WorldBuilder/src/Core/Application.hpp
)

target_include_directories(WorldBuilder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/src
)

set_target_properties(WorldBuilder PROPERTIES
    OUTPUT_NAME WorldBuilder
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_definitions(WorldBuilder PUBLIC
    WB_LOGGER
)

target_compile_options(WorldBuilder PRIVATE
    -std=c++23
    -g
)
