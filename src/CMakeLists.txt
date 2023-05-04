cmake_minimum_required(VERSION 3.25.2)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(terrain-generation)
find_package(GLEW REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

target_link_libraries(terrain-generation PUBLIC
    project_options
    terrain-generation::utils
    terrain-generation::engine
    imgui::imgui
    sfml-graphics sfml-audio sfml-system
    GLEW::GLEW
    ImGui-SFML::ImGui-SFML
)
target_include_directories(terrain-generation PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(terrain-generation PRIVATE
  main.cpp
  "assets/shaders/map.frag"
  "assets/shaders/map.vert"
  "scenes/SceneEnum.h"
  "scenes/MainScene.h"
  "scenes/MainScene.cpp"
)
