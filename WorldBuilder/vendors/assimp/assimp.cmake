message("==== Assimp build (${CMAKE_BUILD_TYPE}) ====")

cmake_minimum_required(VERSION 3.15)

project(TARGET_MODEL_LOADER)

# Disable tests build
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Tests build" FORCE)
# Disable treating warnings as errors
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat warnings as errors" FORCE)
# Disable Assimp's export functionality
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Disable Assimp export functionality" FORCE)
# Enable static library instead of shared
set(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "Build Assimp as a static library" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Assimp as a static library" FORCE)
set(ASSIMP_BUILD_SHARED_LIBS OFF CACHE BOOL "Build Assimp as a static library" FORCE)
# Set additional options as needed
set(ASSIMP_INSTALL OFF CACHE BOOL "Don't install Assimp" FORCE)

set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "build assimp zlib" FORCE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/assimp/assimp/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/WorldBuilder/vendors/assimp/assimp)
#find_package(assimp REQUIRED)
add_library(TARGET_MODEL_LOADER INTERFACE)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties(assimp PROPERTIES
    OUTPUT_NAME assimp
    ARCHIVE_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Assimp"
    LIBRARY_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Assimp"
    RUNTIME_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Assimp"
  )
endif()

target_compile_options(assimp PRIVATE
    -o2
)

target_link_libraries(TARGET_MODEL_LOADER INTERFACE assimp::assimp)
