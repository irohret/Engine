#pragma once

#include <glad/glad.h> 
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

bool loadShader(const char * pathF, const char * pathV, GLuint& program);

