project(ImGuizmo)

add_library(ImGuizmo
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/ImGuizmo/ImGuizmo/ImGuizmo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/ImGuizmo/ImGuizmo/ImGuizmo.cpp
)

target_link_libraries(ImGuizmo PRIVATE
    imgui
)

set_target_properties(ImGuizmo PROPERTIES
    OUTPUT_NAME ImGuizmo
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/ImGuizmo
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/ImGuizmo
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/ImGuizmo
)

target_include_directories(ImGuizmo PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/ImGuizmo/ImGuizmo
)
