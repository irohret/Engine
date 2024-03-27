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
  
std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    
    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return "";
    }
}


Shader::Shader(const char *pathF, const char *pathV) {
    // Read shader and vertex files
    std::string vertexCode = readFileToString(pathV);
    std::string fragmentCode = readFileToString(pathF);

    const char *vertSource = vertexCode.c_str();
    const char *fragSource = fragmentCode.c_str();

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
    }

    // Link shaders into shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for shader program linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::Delete(){
    glUseProgram(ID);
}

void Shader::Activate(){
    glDeleteProgram(ID);
}