#include <time.h>
#include <iostream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <assert.h>
#include <windows.h>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../math/Quaternion.h"
#include "../math/Vector.h"
#include "Bone.h"
#include "Armature.h"
#include "Camera.h"
#include "Window.h"
#include "../shader/Shader.h"

#define WIDTH 1920
#define HEIGHT 1080

using namespace std;

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

float rotationX = 0.0f;
float rotationY = 0.0f;

bool firstMouse = true;

// timing
float deltaTime = 1.0f;
float lastFrame = 0.0f;

void updateInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode){
    const GLfloat cameraSpeed = 2.5f * deltaTime;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch(key){
            case GLFW_KEY_UP:
                rotationX -= cameraSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += cameraSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += cameraSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= cameraSpeed;
                break;
        }
    }
}

int main() {
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW version (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    Window window(WIDTH, HEIGHT, "Test");


    GLuint program;
    const char* pathF = "../shader/test.glslf";
    const char* pathV = "../shader/test.glslv";
    std::cout << "Loading shader..." << std::endl;
    std::cout << "PathF: " << pathF << std::endl;
    std::cout << "PathV: " << pathV << std::endl;

    loadShader(pathF, pathV, program);
    if (!loadShader(pathF, pathV, program)) {
        return -1;
    }

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        0.0f,   0.5f , 0.0f

        //-0.5f, -0.5f, 0.0f,  // bottom left
        // -0.5f,  0.5f, 0.0f   // top left 
    };
    
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        //1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 


    while (!window.shouldClose()) {
        window.pollEvents();
        //updateInput(window);

        // per-frame logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);

        // draw single tringal with 3 points
        glDrawArrays(GL_TRIANGLES, 0, 3);

    
        window.swapBuffers();
        window.pollEvents();
        glFlush();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
