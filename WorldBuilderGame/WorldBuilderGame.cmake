add_executable(WorldBuilderGame
    WorldBuilderGame/src/Game.cpp
)

target_link_libraries(WorldBuilderGame
    WorldBuilder
    glm_math
    EnTT::EnTT
)

target_include_directories(WorldBuilderGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilderGame/src
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/src
)

set_target_properties(WorldBuilderGame PROPERTIES
    OUTPUT_NAME WorldBuilderGame
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilderGame
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilderGame
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/WorldBuilderGame
)

target_compile_definitions(WorldBuilderGame PRIVATE
    # WB_LOGGER
    # WB_ASSERT
)

target_compile_options(WorldBuilderGame PRIVATE
    -o3
)
