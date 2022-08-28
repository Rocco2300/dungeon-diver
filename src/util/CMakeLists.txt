file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/util/*.h")

add_library(util ${SOURCES} ${HEADERS})

target_link_libraries(util PRIVATE sfml-graphics)