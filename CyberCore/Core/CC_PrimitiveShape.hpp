#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include <glm/vec3.hpp>

enum class PrimitiveType {
    CUBE,
    SPHERE,
    CAPSULE,
    CYLINDER,
    QUAD,
    PLANE
};

namespace CyberCore {
    class CC_PrimitiveShape {
    public:
        CC_PrimitiveShape(PrimitiveType type);
        ~CC_PrimitiveShape();

        void createShape(PrimitiveType shapeType);

        std::vector<float>& getVertices();
        std::vector<unsigned int>& getIndices();

    private:
        PrimitiveType type;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        void createCube();
        void createSphere();
        void createCapsule();
        void createCylinder();
        void createQuad();
        void createPlane();
    };
}


