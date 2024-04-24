#pragma once


#include <glm/glm.hpp>
#include <vector>

namespace CyberCore {
    class BoundingBox {

        BoundingBox();
        BoundingBox(glm::vec3 vertices);

        float GetDiagonalLength();
        glm::vec3 GetCenter();

    };
}