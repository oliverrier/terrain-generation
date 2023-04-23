cmake_minimum_required(VERSION 3.25.2)

add_executable(terrain-generation)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)


target_link_libraries(terrain-generation PUBLIC
    project_options
    imgui::imgui
    sfml-graphics sfml-audio sfml-system
    sfml-window
    ImGui-SFML::ImGui-SFML
)
target_include_directories(terrain-generation PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(terrain-generation PRIVATE
  main.cpp
)
