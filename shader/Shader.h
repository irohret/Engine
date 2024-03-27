#pragma once

#include <glad/glad.h> 
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string readFileToString(const std::string& filename);

bool loadShader(const char * pathF, const char * pathV, GLuint& program);

class Shader {
public:
    GLuint ID; 

    // Constructor declaration (without return type)
    Shader(const char * pathF, const char * pathV);

    void Delete();

    // . setVec3("color", glm::vec3 shapeColor)
    void setVec3();

    void Activate();
};
