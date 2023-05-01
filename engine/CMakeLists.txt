cmake_minimum_required(VERSION 3.25.2)

add_library(engine)
add_library(terrain-generation::engine ALIAS engine)

find_package(GLEW REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)


target_link_libraries(engine PUBLIC
    project_options
    terrain-generation::utils
    imgui::imgui
    sfml-graphics sfml-audio sfml-system
    GLEW::GLEW
    ImGui-SFML::ImGui-SFML
)
target_include_directories(engine PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(engine PRIVATE
    "graphics/shaders/Shader.cpp"
    "graphics/shaders/Shader.h"
    "graphics/shape/Cube.h"
)

target_sources(engin PUBLIC
    # MVP
    "MVP/Interfaces.h"
    "MVP/Observable.h"
    "MVP/Signal.h"

    # ImGui
    "ImGui/ImGUIManager.h"
)