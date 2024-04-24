#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glad/glad.h>
#include <string>

namespace CyberCore {
    class CC_StaticMesh{
    public:
        CC_StaticMesh();
        CC_StaticMesh(const CC_StaticMesh &rhs)=default;
        static CC_StaticMesh LoadMesh(const std::string &filename);

    private:
        GLuint VBO, VAO, EBO;
    };
}