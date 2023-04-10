cmake_minimum_required(VERSION 3.25.2)
project(terrain-generation)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" FALSE)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS FALSE)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(CPM)
include(build_configuration)

CPMAddPackage("gh:SFML/SFML#2.6.x")

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

add_subdirectory(game)