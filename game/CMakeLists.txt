cmake_minimum_required(VERSION 3.25.2)

add_executable(terrain-generation)
target_link_libraries(terrain-generation PUBLIC
    project_options
    sfml-graphics sfml-audio sfml-system
)
target_include_directories(terrain-generation PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(terrain-generation PRIVATE
  main.cpp
)
