add_library(glad
    WorldBuilder/vendors/glad/glad/src/glad.c

    WorldBuilder/vendors/glad/glad/include/glad/glad.h
    WorldBuilder/vendors/glad/glad/include/KHR/khrplatform.h
)

target_compile_options(glad PRIVATE
    -std=c17
    -o2
)

set_target_properties(glad PROPERTIES
    OUTPUT_NAME glad
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/glad/glad/include
)
