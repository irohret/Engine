cmake_minimum_required(VERSION 3.5)
project(ARMATURE)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Set include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
)

# Set source files
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/shader/*.cpp
    ${PROJECT_SOURCE_DIR}/math/*.cpp
)

# Set libraries
link_libraries(
    ${OPENGL_LIBRARIES}
    ${GLFW3_LIBRARIES}
    m # Math library
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



#TODO: test this
# 1) create and build: mkdir build && cd build
# 2) run cmake /path/to/project
# 3) run make || cmake --build