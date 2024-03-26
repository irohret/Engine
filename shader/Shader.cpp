#include <glad/glad.h> 
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

bool loadShader(const char * pathF, const char * pathV, GLuint& program) {
    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";

    std::ifstream in_fileF;
    std::ifstream in_fileV;

    in_fileF.open(pathF);
    in_fileV.open(pathV);

    GLuint fragmentShader, vertexShader;

    // Fragment shader
    if (in_fileF.is_open()) {
        while (std::getline(in_fileF, temp)) {
            src += temp + "\n";
        }
        in_fileF.close();

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);  
        const char* src_ptr = src.c_str();
        glShaderSource(fragmentShader, 1, &src_ptr, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Failed to compile fragment shader" << std::endl;
            std::cerr << infoLog << std::endl;  // Print the error log
            return false;
        }
    }

    // Vertex shader
    if (in_fileV.is_open()) {
        src = "";  // Clear the source string for the new shader
        while (std::getline(in_fileV, temp)) {
            src += temp + "\n";
        }
        in_fileV.close();

        // soruce code 
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* src_ptr = src.c_str();
        glShaderSource(vertexShader, 1, &src_ptr, NULL);
        glCompileShader(vertexShader); // machine code

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "Failed to compile vertex shader" << std::endl;
            std::cerr << infoLog << std::endl;  // Print the error log
            return false;
        }
    }

    // Program and linking
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Failed to link program" << std::endl;
        std::cerr << infoLog << std::endl;  // Print the error log
        return false;
    }

    // Clean up: Delete individual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}
  

