#pragma once

#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <string>
#include <cerrno>

// OpenGL && glad
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Define global width and height constants
#define WIDTH 1920
#define HEIGHT 1080

namespace CyberCore {

    class CC_Window {
    public:
        // Constructor to initialize the window with specified width, height, and application name
        CC_Window(int w, int h, const std::string& appName); 
        ~CC_Window();           // Destructor to clean up resources when the window is destroyed

        // Deleted copy constructor and assignment operator to prevent copying of window objects
        CC_Window(const CC_Window&) = delete;
        CC_Window& operator=(const CC_Window&) = delete;

        void run();             // Method to start the main loop of the application
        void quit();            // Method to close the window and terminate the application
        void update();          // Method to update the window

        GLFWwindow* getWindow() { return _window; }      // get the ptr to the window
        inline GLFWwindow& window() { return *_window; } // get the reference to the window

    private:
        void initWindow();      // Method to initialize the GLFW window

        GLFWwindow* _window;    // Method to initialize the GLFW window
        int _width;
        int _height;
        std::string _appName;
        // Static callback function for framebuffer size changes
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);         
    };
}