#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    public: 
        Window(int width, int height, const char* tile);
        ~Window();

        bool createWindow();
        bool shouldClose();
        
        void swapBuffers();

        void pollEvents();

        GLFWwindow* getWindow();

        void ResizeWindow(int width, int height);
        int GetHeight();
        int GetWidth();

    private: 
        GLFWwindow* window;
};