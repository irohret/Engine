#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// gml
#include <glm/vec3.hpp>                     // glm::vec3
#include <glm/vec4.hpp>                     // glm::vec4
#include <glm/mat4x4.hpp>                   // glm::mat4
#include <glm/ext/matrix_transform.hpp>     // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp>    // glm::perspective
#include <glm/ext/scalar_constants.hpp>     // glm::pi


namespace CyberCore {

    class VertexIndexBuffer {
    public:
        VertexIndexBuffer() = default;

        void createBuffer(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        void createBuffer(const std::vector<glm::vec3>& vertices,  const std::vector<unsigned int>& indices);

        void deleteBuffer();

        void bind();

        void unbind();

        void draw(int indexCount);

    private:
        GLuint VBO, VAO, EBO;
    };


    class FrameBuffer {
    public: 
        FrameBuffer() : mFBO {0}, mTextureID {0}, mDepthID{0} {};

        void createFrameBuffer(int32_t _width, int32_t _height);

        void deleteBuffer();

        void bind();

        void unbind();

        uint32_t getTextureID() const { return mTextureID;}
        uint32_t getFBO() const { return mFBO; }

    private:
        uint32_t mFBO = 0;
        uint32_t mTextureID = 0;
        uint32_t mDepthID = 0;
        
        float mWidth, mHeight = 0;
    };

}