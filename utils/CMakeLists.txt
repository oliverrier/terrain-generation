cmake_minimum_required(VERSION 3.25.2)


add_library(utils)
add_library(terrain-generation::utils ALIAS utils)
target_link_libraries(utils PUBLIC
    project_options
)
target_include_directories(utils PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(utils PRIVATE
  "link.cpp"
  "math/Math.h"
 "design_patterns/Factory.h" "design_patterns/TypeList.h" "math/Vector2.h")