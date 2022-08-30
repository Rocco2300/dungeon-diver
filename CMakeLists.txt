cmake_minimum_required(VERSION 3.20)

project(dungeon_diver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

link_directories(
    "${PROJECT_SOURCE_DIR}/lib/SFML"
)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/ui"
    "${PROJECT_SOURCE_DIR}/include/util"
    "${PROJECT_SOURCE_DIR}/include/asset"
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_definitions(/DPROJ_PATH="${PROJECT_SOURCE_DIR}/")
else()
    add_definitions(-DPROJ_PATH="${PROJECT_SOURCE_DIR}/")
endif()

add_executable(dungeon_diver "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_subdirectory(src)

file(GLOB TARGET_DLLS "${PROJECT_SOURCE_DIR}/lib/bin/*.dll")

add_custom_command(TARGET dungeon_diver
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${TARGET_DLLS} $<TARGET_FILE_DIR:dungeon_diver>
)

target_link_libraries(dungeon_diver PUBLIC src)
target_link_libraries(dungeon_diver PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)