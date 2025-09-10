add_executable(WorldBuilderEditor
    WorldBuilderEditor/src/Editor.cpp
    WorldBuilderEditor/src/Editor.hpp

    WorldBuilderEditor/src/UIEditor/CommandLineBarLayer.cpp
    WorldBuilderEditor/src/UIEditor/CommandLineBarLayer.hpp
    WorldBuilderEditor/src/UIEditor/ImGuiAdditionals.cpp
    WorldBuilderEditor/src/UIEditor/ImGuiAdditionals.hpp
    WorldBuilderEditor/src/UIEditor/MainMenuBarLayer.cpp
    WorldBuilderEditor/src/UIEditor/MainMenuBarLayer.hpp
    WorldBuilderEditor/src/UIEditor/EditorShortcutInputManager.hpp
    WorldBuilderEditor/src/UIEditor/EditorShortcutInputManager.cpp
    WorldBuilderEditor/src/UIEditor/ViewportLayer.hpp
    WorldBuilderEditor/src/UIEditor/ViewportLayer.cpp
        WorldBuilderEditor/src/UIEditor/ProjectEditor/CreateProjectEditorLayer.hpp
        WorldBuilderEditor/src/UIEditor/ProjectEditor/CreateProjectEditorLayer.cpp
        WorldBuilderEditor/src/UIEditor/ProjectEditor/OpenProjectEditorLayer.hpp
        WorldBuilderEditor/src/UIEditor/ProjectEditor/OpenProjectEditorLayer.cpp
        WorldBuilderEditor/src/UIEditor/RessourcesLayer/RessourcesLayer.hpp
        WorldBuilderEditor/src/UIEditor/RessourcesLayer/RessourcesLayer.cpp
        WorldBuilderEditor/src/UIEditor/RessourcesLayer/RessourceEditorItem.hpp
        WorldBuilderEditor/src/UIEditor/RessourcesLayer/RessourceEditorItem.cpp
        WorldBuilderEditor/src/UIEditor/RessourcesLayer/AssetSelectorLayer.hpp
        WorldBuilderEditor/src/UIEditor/RessourcesLayer/AssetSelectorLayer.cpp
        WorldBuilderEditor/src/UIEditor/Hierarchy/HierarchyLayer.hpp
        WorldBuilderEditor/src/UIEditor/Hierarchy/HierarchyLayer.cpp
        WorldBuilderEditor/src/UIEditor/Inspector/Inspector.hpp
        WorldBuilderEditor/src/UIEditor/Inspector/Inspector.cpp
)

target_link_libraries(WorldBuilderEditor
    WorldBuilder
    glm_math
    imgui
    EnTT::EnTT
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
