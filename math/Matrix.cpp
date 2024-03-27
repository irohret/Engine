
#include <math.h>
#include <iostream>

#include "Matrix.h"

Matrix4x4 MatixTranslation(double tx, double ty, double tz) {
    Matrix4x4 translationMatrix = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}
    };
    return translationMatrix;
}

Matrix4x4 MatrixRotationXaxis(double theta) {
    Matrix4x4 rotationMatrixX = {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };
    return rotationMatrixX;
}

Matrix4x4 MatrixRotationYaxis(double theta) {
    Matrix4x4 rotationMatrixY = {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };
    return rotationMatrixY;
}

Matrix4x4 MatrixRotationZaxis(double theta) {
     Matrix4x4 rotationMatrixZ = {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return rotationMatrixZ;
}


Matrix4x4 MatrixScale(double sx, double sy, double sz) {
    Matrix4x4 scaleMatrix = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    return scaleMatrix;
}

void printMatrix(const Matrix4x4& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}