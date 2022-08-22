file(GLOB SOURCES "*.cpp")
list(REMOVE_ITEM SOURCES "main.cpp")

add_subdirectory(ui)
add_subdirectory(util)

add_library(src ${SOURCES})

target_link_libraries(src PUBLIC ui)
target_link_libraries(src PUBLIC util)