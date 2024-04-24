#include "CC_Camera.hpp"


namespace CyberCore {

    CC_Camera::CC_Camera(int width, int height, glm::vec3 position){
        CC_Camera::width = width;
        CC_Camera::height = height;
        Position = position;
    }
    


    // void CC_Camera::Matrix_T(float FOV, float nearPlane, float farPlane, Shader &shader, const char uniform) {} 
    void CC_Camera::Matrix(float FOV, float nearPlane, float farPlane){
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = glm::lookAt(Position, Position + Orientation, Up);

        //projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);

        projection = glm::perspective(glm::radians(FOV), (float)(width/height), nearPlane, farPlane);
        //glUniformMatrix4fv(glGetUniformLocation(ShaderID, uniform), 1, GL_FALSE, &projection[0][0]);
    }

    void CC_Camera::Inputs(GLFWwindow *window){

    }
  

   
} // namespace CyberCore
