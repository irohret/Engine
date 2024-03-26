# Compiler and flags
CXX = g++
CXXFLAGS = -g --std=c++17
LIBRARIES = -lm -lglfw3dll 

# Directories
INCLUDE_DIR = ../include
LIB_DIR = ../lib
SRC_DIR = ../src
SHD_DIR = ../shader
MTH_DIR = ../math

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(SRC_DIR)/glad.c $(SHD_DIR)/Shader.cpp 

# Output target
TARGET = main

# Build rule
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) $^ $(LIBRARIES) -o $@

# Clean rule
clean:
	rm -f $(TARGET)
