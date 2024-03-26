#pragma once

#include <math.h>
#include <iostream>


#include "Vector.h"

using Matrix4x4 = std::vector<std::vector<double>>;

// Define a 3D vector
using Vector3 = std::vector<float>;

Matrix4x4 MatixTranslation(double tx, double ty, double tz);

Matrix4x4 MatrixRotation(double theta);

Matrix4x4 MatrixRotationXaxis(double theta);

Matrix4x4 MatrixRotationYaxis(double theta);

Matrix4x4 MatrixRotationZaxis(double theta);

Matrix4x4 createRotationMatrixZ(double theta);

Matrix4x4 MatrixScale(double sx, double sy, double sz);

Matrix4x4 MatrixTransformation();

void printMatrix(const Matrix4x4& matrix);

