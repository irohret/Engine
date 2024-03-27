#include "VAO.h"
#include <glad/glad.h>

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

// link a VBO to a VBA
void VAO::linkVBO(VBO& VBO, GLuint layout){
    VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.unBind();
}

void VAO::Bind(){
    glBindVertexArray(ID);
}
void VAO::unBind(){
    glBindVertexArray(0);
}

void VAO::Delete(){
    glDeleteVertexArrays(1, &ID);
}