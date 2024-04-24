cmake_minimum_required(VERSION 3.24)
project(tiny)

add_library(tiny INTERFACE)

target_sources(tiny INTERFACE tiny_obj_loader.h)

target_include_directories(tiny
    INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
