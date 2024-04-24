#include "CC_Window.h"

namespace CyberCore {

    CC_Window::CC_Window(int w, int h, const std::string& appName)
        : _width(w), _height(h), _appName(appName) {
        initWindow();
    }

    CC_Window::~CC_Window() {
        quit();
    }

    void CC_Window::quit() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void CC_Window::update() {
        // update logic???
        // main looop 
        // while (!glfwWindowShouldClose(window.getWindow())) ..
    }

    void CC_Window::initWindow() {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        _window = glfwCreateWindow(_width, _height, _appName.c_str(), nullptr, nullptr);

        if (!_window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(_window);

         // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);  glGetError();
       //  glDebugMessageCallback(glDebugMessageCallback, 0);

           // Set OpenGL viewport size
        glViewport(0, 0, WIDTH, HEIGHT); glGetError();
        glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
    }

    void CC_Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);  glGetError();
    }
}