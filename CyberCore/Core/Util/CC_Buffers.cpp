#include "CC_Buffers.hpp"

namespace CyberCore {

    // --------- Vertex Index Buffer ---------

    void VertexIndexBuffer::createBuffer(const std::vector<float>& vertices,  const std::vector<unsigned int>& indices ){

    glGenVertexArrays(1, &VAO); glGetError();

    glGenBuffers(1, &VBO); glGetError();
    glGenBuffers(1, &EBO); glGetError();

    glBindVertexArray(VAO); glGetError();

    glBindBuffer(GL_ARRAY_BUFFER, VBO); glGetError();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); glGetError();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); glGetError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);  glGetError();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glGetError();
    glEnableVertexAttribArray(0); glGetError();

    glBindBuffer(GL_ARRAY_BUFFER, 0); glGetError();
    glBindVertexArray(0); glGetError();

    }

    void VertexIndexBuffer::createBuffer(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices) {
        glGenVertexArrays(1, &VAO); glGetError();
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO); glGetError();

        glBindVertexArray(VAO); glGetError();

        glBindBuffer(GL_ARRAY_BUFFER, VBO); glGetError();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW); glGetError();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); glGetError();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); glGetError();

        // Specify the layout of the vertex data
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    }


    void VertexIndexBuffer::deleteBuffer(){
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void VertexIndexBuffer::bind(){
        glBindVertexArray(VAO);
    }

    void VertexIndexBuffer::unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void VertexIndexBuffer::draw(int indexCount){
        bind();

        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr); glGetError();

        unbind();
    }

    // --------- Frame Buffer ---------

void FrameBuffer::createFrameBuffer(int32_t width, int32_t height)  {
    mWidth = width;
    mHeight = height;

    if(mFBO){
        FrameBuffer::deleteBuffer();
    }

   // Generate framebuffer object
    glGenFramebuffers(1, &mFBO); glGetError();
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO); glGetError();

    // Create color attachment texture a,ka create color texture
    
    glGenTextures(1, &mTextureID); glGetError();
    glBindTexture(GL_TEXTURE_2D, mTextureID); glGetError();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); glGetError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glGetError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); glGetError();
    glBindTexture(GL_TEXTURE_2D, 0); glGetError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureID, 0); glGetError();
   
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureID, 0);

    // Create depth/stecnil attachment texture
    glGenRenderbuffers(1, &mDepthID); glGetError();
    glBindRenderbuffer(GL_TEXTURE_2D, mDepthID); glGetError();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight); glGetError();
    glBindRenderbuffer(GL_RENDERBUFFER, 0); glGetError();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthID); glGetError();
    // glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthID, 0);

    // Specify the draw buffers
    // GLenum buffers[3] = { GL_COLOR_ATTACHMENT0 };
    // glDrawBuffers(mTextureID, buffers);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer is not complete!" << std::endl;
    }

    // Unbind framebuffer
    FrameBuffer::unbind();
}


    void FrameBuffer::deleteBuffer(){
      glDeleteFramebuffers(GL_FRAMEBUFFER, &mFBO);
      glDeleteTextures(1, &mTextureID);
      glDeleteTextures(1, &mDepthID);
    }

    void FrameBuffer::unbind(){
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
        glViewport(0, 0, mWidth, mHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void FrameBuffer::bind(){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}