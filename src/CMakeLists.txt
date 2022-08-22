file(GLOB SOURCES "*.cpp")
list(REMOVE_ITEM SOURCES "main.cpp")

add_library(src ${SOURCES})