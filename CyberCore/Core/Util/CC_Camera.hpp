#pragma once

// gml
#include <glm/vec3.hpp>                     // glm::vec3
#include <glm/vec4.hpp>                     // glm::vec4
#include <glm/mat4x4.hpp>                   // glm::mat4
#include <glm/ext/matrix_transform.hpp>     // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp>    // glm::perspective
#include <glm/ext/scalar_constants.hpp>     // glm::pi

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


enum Camera_Movement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


namespace CyberCore {

    class CC_Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
       

        int width;
        int height;

        float yaw;
        float pitch;

        float speed = 0.0f;
        float sensitivity = 100.0f;
        float panSpeed = 0.001f;

        CC_Camera(int width, int height, glm::vec3 position);
        
        // void Matrix_T(float FOV, float nearPlane, float farPlane, Shader &shader, const char uniform);
        void Matrix(float FOV, float nearPlane, float farPlane);
        
        void Inputs(GLFWwindow *window);

    private:
        const glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        
    };

} // namespace CyberCore

