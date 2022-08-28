file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

list(REMOVE_ITEM SOURCES "main.cpp")

add_subdirectory(ui)
add_subdirectory(util)
add_subdirectory(asset)


add_library(src ${SOURCES} ${HEADERS})

target_link_libraries(src PUBLIC ui)
target_link_libraries(src PUBLIC util)
target_link_libraries(src PUBLIC asset)