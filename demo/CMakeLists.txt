# © 2020 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/simple-glfw")

jfc_project(executable
    NAME "gdktilerenderer-demo"
    VERSION 1.0
    DESCRIPTION "gdk-tile_renderer demonstration"
    C++_STANDARD 17
    C_STANDARD 90

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

    PRIVATE_INCLUDE_DIRECTORIES
        "${gdktilerenderer_INCLUDE_DIRECTORIES}"
        "${simpleglfw_INCLUDE_DIRECTORIES}"

    LIBRARIES
        "${gdktilerenderer_LIBRARIES}"
        "${simpleglfw_LIBRARIES}"

    DEPENDENCIES
        "gdktilerenderer"
        "simpleglfw"
)

