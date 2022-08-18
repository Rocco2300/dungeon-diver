cmake_minimum_required(VERSION 3.20)

project(dungeon_diver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

link_directories(
    "${PROJECT_SOURCE_DIR}/lib/SFML"
)

include_directories(
    "${PROJECT_SOURCE_DIR}/include/"
    "${PROJECT_SOURCE_DIR}/include/SFML/"
    "${PROJECT_SOURCE_DIR}/"
)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(dungeon_diver ${SOURCES})

file(GLOB TARGET_DLLS "${PROJECT_SOURCE_DIR}/lib/bin/*.dll")

add_custom_command(TARGET dungeon_diver
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
  ${TARGET_DLLS} ${PROJECT_BINARY_DIR}
)

target_link_libraries(dungeon_diver sfml-graphics sfml-window sfml-audio sfml-system)