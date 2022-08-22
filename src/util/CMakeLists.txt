file(GLOB SOURCES "*.cpp")

add_library(util ${SOURCES})

target_link_libraries(util PRIVATE sfml-graphics)