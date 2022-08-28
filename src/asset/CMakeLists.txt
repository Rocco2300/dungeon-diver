file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/asset/*.h")

add_library(asset ${SOURCES} ${HEADERS})

target_link_libraries(asset PRIVATE sfml-graphics sfml-audio)
