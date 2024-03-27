#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO {
    public:
        GLuint ID;

        // Constructor declaration (without return type)
        VAO();

        void linkVBO(VBO& VBO, GLuint layout);

        void Bind();
        void unBind();

        void Delete();
    };
