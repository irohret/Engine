#include "CC_PrimitiveShape.hpp"

namespace CyberCore {
    // CC_PrimitiveShape::CC_PrimitiveShape() {

    // }

    CC_PrimitiveShape::CC_PrimitiveShape(PrimitiveType shapeType) : type(shapeType) {
        createShape(shapeType);
    }


    CC_PrimitiveShape::~CC_PrimitiveShape() {

    }

    void CC_PrimitiveShape::createShape(PrimitiveType shapeType) {
        switch (shapeType) {
            case PrimitiveType::CUBE:
                createCube();
                break;
            case PrimitiveType::SPHERE:
                createSphere();
                break;
            case PrimitiveType::CAPSULE:
                createCapsule();
                break;
            case PrimitiveType::CYLINDER:
                createCylinder();
                break;
            case PrimitiveType::QUAD:
                createQuad();
                break;
            case PrimitiveType::PLANE:
                createPlane();
                break;
            default:
                break;
        }
    }

    std::vector<float>& CC_PrimitiveShape::getVertices() {
        return vertices;
    }

    std::vector<unsigned int>& CC_PrimitiveShape::getIndices() {
        return indices;
    }

    void CC_PrimitiveShape::createCube() {
        // Define vertices for a cube
        float verticesArray[] = {
            // front face
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            // back face
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
        };

        // Define indices for a cube
        unsigned int indicesArray[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            1, 5, 6,
            6, 2, 1,
            0, 4, 7,
            7, 3, 0,
            3, 2, 6,
            6, 7, 3,
            0, 1, 5,
            5, 4, 0
        };

        vertices.insert(vertices.end(), std::begin(verticesArray), std::end(verticesArray));
        indices.insert(indices.end(), std::begin(indicesArray), std::end(indicesArray));
    }

    void CC_PrimitiveShape::createSphere() {
        const int sectorCount = 36;
        const int stackCount = 18;
        const float radius = 0.5f;

        float x, y, z, xy;
        float sectorStep = 2 * M_PI / sectorCount;
        float stackStep = M_PI / stackCount;
        float sectorAngle, stackAngle;

        for (int i = 0; i <= stackCount; ++i) {
            stackAngle = M_PI / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectorCount; ++j) {
                sectorAngle = j * sectorStep;

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }

        int k1, k2;
        for (int i = 0; i < stackCount; ++i) {
            k1 = i * (sectorCount + 1);
            k2 = k1 + sectorCount + 1;

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if (i != (stackCount - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }
    }

    void CC_PrimitiveShape::createCapsule(){ }
    void CC_PrimitiveShape::createCylinder() { }
    void CC_PrimitiveShape::createQuad() { }
    void CC_PrimitiveShape::createPlane(){ } 
}