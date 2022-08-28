file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/ui/*.h")

add_library(ui ${SOURCES} ${HEADERS})

target_link_libraries(ui PRIVATE sfml-graphics)
