cmake_minimum_required(VERSION 3.5)
project(CyberCore_Engine VERSION 1.0.0)

if(WIN32)
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    MESSAGE("==================== USING MSVC TO COMILE ====================")
    add_compile_options(/wd4819 /wd4244 /wd4267 /wd4305 "/Zc:__cplusplus")
    set(CMAKE_CXX_FLAGS_DEBUG "/O2")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
  else()
    MESSAGE("==================== USING MINGW TO COMILE ====================")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  endif()
else()
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O3")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Check if Git is available
find_package(Git QUIET)

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULES "Check Submodules during build" ON)
    if(GIT_SUBMODULES)
        message(STATUS "Submodules update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if(NOT ${GIT_SUBMODULE_RESULT} EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive  failed with ${GIT_SUBMODULE_RESULT}, please checkout submodules!")
        endif()
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)

# Set build type if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenGL REQUIRED)

# add Vulkan and SDL
add_subdirectory(CyberCore/Vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(CyberCore/Vendor/glm EXCLUDE_FROM_ALL)
add_subdirectory(CyberCore/Vendor/SDL)
add_subdirectory(CyberCore/Vendor/Vulkan-Headers)

# Include ImGui from CyberCore/Vendor/imgui
add_subdirectory(CyberCore/Vendor/imgui)


add_executable(CyberCore_Engine
    CyberCoreEngine/src/config.h
    CyberCoreEngine/src/main.cpp 
    CyberCore/Vendor/glad/glad.c
    CyberCore/Vendor/imgui/imgui.h
    CyberCore/Vendor/imgui/backends/imgui_impl_glfw.cpp
    CyberCore/Vendor/imgui/backends/imgui_impl_glfw.h
    CyberCore/Vendor/imgui/backends/imgui_impl_opengl3.cpp
    CyberCore/Vendor/imgui/backends/imgui_impl_opengl3.h
)

# Add include directories for linking
target_include_directories(CyberCore_Engine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor 
    ${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/imgui 
    ${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/imgui/backends 
)

# Link GLFW, ImGui, and OpenGL libraries
target_link_libraries(CyberCore_Engine 
    glfw
    SDL3::SDL3
    ImGui 
    Vulkan::Headers
)

add_custom_command(TARGET CyberCore_Engine
    POST_BUILD
    COMMAND ./CyberCore_Engine
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Engine after build"
)
