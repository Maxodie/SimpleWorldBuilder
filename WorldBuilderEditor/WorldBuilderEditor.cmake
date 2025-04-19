add_executable(WorldBuilderEditor
    WorldBuilderEditor/src/Editor.cpp
)

target_link_libraries(WorldBuilderEditor
    WorldBuilder
    glm_math
)

target_include_directories(WorldBuilderEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilderEditor/src
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/src
)

set_target_properties(WorldBuilderEditor PROPERTIES
    OUTPUT_NAME WorldBuilderEditor
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilderEditor
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilderEditor
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilderEditor
)

target_compile_definitions(WorldBuilderEditor PRIVATE
    WB_LOGGER
    WB_ASSERT
)
