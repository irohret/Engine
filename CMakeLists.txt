# main CMakeLists.txt
cmake_minimum_required(VERSION 3.24)
project(CyberCore_Application VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CheckOBJCSourceCompiles)
if(APPLE)
    enable_language(OBJC)
endif()

if(WIN32)
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    MESSAGE("==================== USING MSVC TO COMPILE ====================")
    add_compile_options(/wd4819 /wd4244 /wd4267 /wd4305 "/Zc:__cplusplus")
    set(CMAKE_CXX_FLAGS_DEBUG "/O2")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
  else()
    MESSAGE("==================== USING MINGW TO COMPILE ====================")
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
include_directories(CyberCore/Vendor/SDL)
include_directories(CyberCore/Vendor/imgui)
include_directories(CyberCore/Vendor/imgui/backends)
include_directories(CyberCore/Vendor/glad/include)
include_directories(CyberCore/Vendor/SDL/src/)
include_directories(CyberCore/Vendor/glm)
include_directories(CyberCore/Vendor/Vulkan-Headers)
include_directories(CyberCore/Vendor/stb_image)
include_directories(CyberCore/Vendor/tiny)
include_directories(CyberCore/Vendor/assimp/include)
include_directories(CyberCore/Vendor/assimp)

set(STB_IMAGE CyberCore/Vendor/stb_image/stb_image.h)
set(TINY_OBJECT_LOADER CyberCore/Vendor/tiny/tiny_obj_loader.h) 

set(SDL_HEADERS
    CyberCore/Vendor/SDL/include/SDL3/SDL.h
    CyberCore/Vendor/SDL/include/SDL3/SDL_stdinc.h
    CyberCore/Vendor/SDL/include/build_config/SDL_build_config.h
    CyberCore/Vendor/SDL/src/SDL_internal.h
    CyberCore/Vendor/SDL/src/core/linux/SDL_dbus.h
    CyberCore/Vendor/SDL/src/core/linux/SDL_dbus.h
    CyberCore/Vendor/SDL/src/audio/SDL_sysaudio.h
    CyberCore/Vendor/SDL/src/events/SDL_events_c.h
)

set(SDL_SOURCES
    CyberCore/Vendor/SDL/src/SDL.c  
)

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

# Define CORE sources and headers
set(CORE_HEADER
    CyberCore/Core/CC_ImGuI.h
    CyberCore/Core/CC_Window.h
    CyberCore/Core/Panel/HierarchyPanel.hpp
    CyberCore/Core/Panel/InspectorPanel.hpp
    CyberCore/Core/Panel/ProjectPanel.hpp
    CyberCore/Core/Panel/ScenePanel.hpp
    CyberCore/Core/Panel/GamePanel.hpp
    CyberCore/Core/CC_Time.hpp
    CyberCore/Core/CC_PrimitiveShape.hpp
    CyberCore/Core/Util/CC_Camera.hpp
    CyberCore/Core/Shader/CC_Shader.hpp
    CyberCore/Core/Util/CC_Buffers.hpp
)

set(CORE_SOURCES
    CyberCore/Core/CC_ImGuI.cpp
    CyberCore/Core/CC_Window.cpp
    CyberCore/Core/Panel/HierarchyPanel.cpp
    CyberCore/Core/Panel/InspectorPanel.cpp
    CyberCore/Core/Panel/ProjectPanel.cpp
    CyberCore/Core/Panel/ScenePanel.cpp
    CyberCore/Core/Panel/GamePanel.cpp
    CyberCore/Core/CC_Time.cpp
    CyberCore/Core/CC_PrimitiveShape.cpp
    CyberCore/Core/Util/CC_Camera.cpp
    CyberCore/Core/Shader/CC_Shader.cpp
    CyberCore/Core/Util/CC_Buffers.cpp
)

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/SDL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/stb_image)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cyberCore/Vendor/tiny)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CyberCore/Vendor/assimp)

# Override compiler flags for Assimp target
if(WIN32)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC") # For MSVC compiler
        target_compile_options(assimp PRIVATE /W0)  # Disable all warnings for Assimp
    else()
        target_compile_options(assimp PRIVATE -w)   # Disable all warnings for Assimp For other compilers (e.g., MinGW)
    endif()
else()
    # For non-Windows platforms
    target_compile_options(assimp PRIVATE -w)       # Disable all warnings for Assimp
endif()

# Add executable
if(WIN32)
    # prevent CMD prompt window pops up on execution. (WIN32)
add_executable(${PROJECT_NAME}  CyberCoreEngine/src/main.cpp ${TINY_OBJECT_LOADER}  ${STB_IMAGE} ${CORE_HEADER} ${CORE_SOURCES} ${SDL_HEADERS} ${SDL_SOURCES} ${CONFIG} ${IMGUI_SOURCES} ${IMGUI_HEADERS})
else()
      add_executable(${PROJECT_NAME} CyberCoreEngine/src/main.cpp  ${TINY_OBJECT_LOADER} ${STB_IMAGE} ${CORE_HEADER} ${CORE_SOURCES} ${SDL_HEADERS} ${SDL_SOURCES} ${CONFIG} ${IMGUI_SOURCES} ${IMGUI_HEADERS})
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} assimp glfw glm glad SDL3::SDL3)

target_compile_definitions(${PROJECT_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# if(APPLE)
#     add_custom_command(TARGET ${PROJECT_NAME}
#         POST_BUILD
#         COMMAND ./${PROJECT_NAME}
#         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#         COMMENT "Running Engine after build"
#     )
# endif()
