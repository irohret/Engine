# Compiler and flags
CXX = g++
CXXFLAGS = -g --std=c++17
LIBRARIES = -lm -lglfw3dll

# Directories
IMGUI_DIR = ../include/imgui
INCLUDE_DIR = ../include
LIB_DIR = ../lib
SRC_DIR = ../src
WINDOW_DIR = ../src/Window
SHD_DIR = ../shader
MTH_DIR = ../math
BIN_DIR = ../bin # contains glfw3.dll file along with the Makefile

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) \
            $(INCLUDE_DIR)/glad.c \
            $(SHD_DIR)/VAO.cpp \
            $(SHD_DIR)/VBO.cpp \
            $(SHD_DIR)/EBO.cpp \
            $(SHD_DIR)/Shader.cpp \
            $(WINDOW_DIR)/Window.cpp\
            $(MTH_DIR)/Matrix.cpp \
            $(MTH_DIR)/Vector.cpp \
            $(MTH_DIR)/Quaternion.cpp \


IMGUI_SRC_FILES = $(wildcard $(IMGUI_DIR)/*.cpp) \
                  $(IMGUI_DIR)/backend/imgui_impl_opengl3.cpp \
                  $(IMGUI_DIR)/backend/imgui_impl_glfw.cpp\
				 


# Output target
TARGET = main

# Build rule
all: $(TARGET)

$(TARGET): $(SRC_FILES) $(IMGUI_SRC_FILES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(IMGUI_DIR) -L$(LIB_DIR) -L$(BIN_DIR) -L$(SHD_DIR) -L$(MTH_DIR) $^ $(LIBRARIES) -o $@

# Clean rule
clean:
	rm -f $(TARGET)