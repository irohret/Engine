#include <time.h>
#include <iostream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <assert.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include "../include/imgui/imgui.h"
#include "../include/imgui/backend/imgui_impl_glfw.h"
#include "../include/imgui/backend/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../math/Quaternion.h"
#include "../math/Vector.h"
#include "Bone.h"
#include "Armature.h"
#include "Camera.h"
#include "../src/Window/Window.h"
#include "../shader/Shader.h"
#include "../shader/VAO.h"
#include "../shader/VBO.h"
#include "../shader/EBO.h"
#include "ImGui.h"

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


void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode) {
    const GLfloat cameraSpeed = 2.5f * deltaTime;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
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

    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    Window window(WIDTH, HEIGHT, "Test");
    ImGuiManager imGuiManager;

    imGuiManager.SetDisplaySize(static_cast<float>(WIDTH/2), static_cast<float>(HEIGHT/2));
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    const char* pathF = "../shader/test.glslf";
    const char* pathV = "../shader/test.glslv";

    std::cout << "Loading shader..." << std::endl;
    std::cout << "PathF: " << pathF << std::endl;
    std::cout << "PathV: " << pathV << std::endl;

    Shader shader(pathF, pathV);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
         0.0f,  0.5f, 0.0f   // top
    };

    unsigned int indices[] = {
        0, 1, 2  // first triangle
    };

    VAO _VAO;
    _VAO.Bind();
    VBO _VBO(vertices, sizeof(vertices));
    EBO _EBO(indices, sizeof(indices));
    _VAO.linkVBO(_VBO, 0);
    _VBO.unBind();
    _VAO.unBind();
    _EBO.unBind();

    float triangleColor[3] = {1.0f, 1.0f, 1.0f};

    while (!window.shouldClose()) {
        window.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        imGuiManager.BeginFrame();
        
        // ImGui window to change triangle color
        {
            ImGui::Begin("Color Picker");

            //static ImVec4 color = ImVec4(1.0f, 0.5f, 0.2f, 1.0f);
            ImGui::ColorEdit3("Triangle Color", triangleColor);

            ImGui::End();
        }

        // render IMGUI
        imGuiManager.Render();
        int display_w, display_h;

        glfwGetFramebufferSize(window.getWindow(), &display_w, &display_h);
    
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        imGuiManager.EndFrame();

        // per-frame logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        shader.Activate();
        glUniform3fv(glGetUniformLocation(shader.ID, "color"), 1, triangleColor);

        _VAO.Bind();

        // draw single triangle with 3 points
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Render ImGui
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
        window.pollEvents();
        glFlush();
    }

    // clean up 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    _VBO.Delete();
    _VAO.Delete();
    _EBO.Delete();
    shader.Delete();

    window.~Window();

    glfwTerminate();

    return 0;
}