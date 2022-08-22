file(GLOB SOURCES "*.cpp")

add_library(ui ${SOURCES})

target_link_libraries(ui PRIVATE sfml-graphics)