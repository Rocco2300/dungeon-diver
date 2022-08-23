file(GLOB SOURCES "*.cpp")

add_library(asset ${SOURCES})

target_link_libraries(asset PRIVATE sfml-graphics sfml-audio)
