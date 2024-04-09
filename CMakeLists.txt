# main CMakeLists.txt
cmake_minimum_required(VERSION 3.24)
project(CyberCore_Application VERSION 1.0.0)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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



# Check if Git is available (used for git submodules)
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


# Include directories
include_directories(CyberCore/Vendor/glfw/include)
include_directories(CyberCore/Vendor/imgui)
include_directories(CyberCore/Vendor/imgui/backends)
include_directories(CyberCore/Vendor/glad/include)

set(IMGUI_SOURCES
    CyberCore/Vendor/imgui/imgui.cpp
    CyberCore/Vendor/imgui/imgui_demo.cpp
    CyberCore/Vendor/imgui/imgui_draw.cpp
    CyberCore/Vendor/imgui/imgui_tables.cpp
    CyberCore/Vendor/imgui/imgui_widgets.cpp
    CyberCore/Vendor/imgui/backends/imgui_impl_glfw.cpp
    CyberCore/Vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# Define ImGui headers
set(IMGUI_HEADERS
    CyberCore/Vendor/imgui/imgui.h
    CyberCore/Vendor/imgui/imgui_internal.h
    CyberCore/Vendor/imgui/imconfig.h
    CyberCore/Vendor/imgui/imstb_rectpack.h
    CyberCore/Vendor/imgui/imstb_textedit.h
    CyberCore/Vendor/imgui/imstb_truetype.h
    CyberCore/Vendor/imgui/backends/imgui_impl_glfw.h
    CyberCore/Vendor/imgui/backends/imgui_impl_opengl3.h
)

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/glad)


# Add executable
# add_executable(${PROJECT_NAME} CyberCoreEngine/src/main.cpp ${IMGUI_SOURCES} ${IMGUI_HEADERS})

if(WIN32)
    # prevent CMD prompt window pops up on execution. (WIN32)
    add_executable(${PROJECT_NAME} WIN32 CyberCoreEngine/src/main.cpp ${IMGUI_SOURCES} ${IMGUI_HEADERS})
else()
    add_executable(${PROJECT_NAME} CyberCoreEngine/src/main.cpp ${IMGUI_SOURCES} ${IMGUI_HEADERS})
endif()


# Link libraries
target_link_libraries(${PROJECT_NAME} glfw glad)

# add_custom_command(TARGET ${PROJECT_NAME}
#     POST_BUILD
#     COMMAND ./${PROJECT_NAME}
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     COMMENT "Running Engine after build"
# )
