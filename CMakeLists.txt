cmake_minimum_required(VERSION 3.5)
project(CyberCore_Engine VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

if(CMAKE_COMPILER_IS_GNUCCXX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(CMAKE_COMPILER_IS_GNUCCXX)


# Check if Git is available
find_package(Git QUIET)

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULES "Check Submodules during build" ON)
    if(GIT_SUBMODULES)
        message(STATUS "Submodules update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive  failed with ${GIT_SUBMOD_RESULT}, please checkout submodules!")
        endif()
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenGL REQUIRED)

add_subdirectory(CyberCore/Vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(CyberCore/Vendor/glm EXCLUDE_FROM_ALL)

# Generate CMakeLists.txt for ImGui
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/imgui/CMakeLists.txt
    "add_library(imgui STATIC\n"
    "    imgui.cpp\n"
    "    imgui_demo.cpp\n"
    "    imgui_draw.cpp\n"
    "    imgui_widgets.cpp\n"
    ")\n\n"
    "# Include directory for ImGui\n"
    "target_include_directories(imgui PUBLIC\n"
    "    \${CMAKE_CURRENT_SOURCE_DIR}\n"
    ")\n"
)

# Include ImGui from CyberCore/Vendor/imgui
add_subdirectory(CyberCore/Vendor/imgui)

add_executable(CyberCore_Engine
    CyberCoreEngine/src/config.h
    CyberCoreEngine/src/main.cpp 
    CyberCore/Vendor/glad/glad.c
)

# Add include directories for linking
target_include_directories(CyberCore_Engine 
    PRIVATE
    CyberCore/Vendor 
)

# Link GLFW, ImGui, and OpenGL libraries
target_link_libraries(CyberCore_Engine
    glfw
    imgui
    OpenGL::GL 
)

add_custom_command(TARGET CyberCore_Engine
    POST_BUILD
    COMMAND ./CyberCore_Engine
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Engine after build"
)