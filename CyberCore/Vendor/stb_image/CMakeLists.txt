cmake_minimum_required(VERSION 3.24)
project(stb_image)

add_library(stb_image INTERFACE)

target_sources(stb_image INTERFACE stb_image.h)

target_include_directories(stb_image
    INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h"
)