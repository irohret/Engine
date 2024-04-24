#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"
#include <glm/ext.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi



namespace CyberCore {
    class CC_Shader {
    public:
        CC_Shader() = default;

        bool createShader(const std::string& VertexShader, const std::string& fragmentShader);

        unsigned int getShaderID() { return shaderID; }

        void useShader(); // Use the program

        void deleteShader(); // Delete the program

        void setMat4(const glm::mat4& mat4, const std::string& src);
        
        void setVec3(const glm::vec3& vec3, const std::string& src);

        void setVec4(const glm::vec3& vec3, const std::string& src);


        void set_i1(int v, const std::string& name);
		void set_f1(float v, const std::string& name);
		void set_f3(float a, float b, float c, const std::string& name);


    private:
        unsigned int shaderID;
        unsigned int load(unsigned int shaderType, const std::string& shaderSRC);

    };
}