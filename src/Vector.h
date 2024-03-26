#pragma once

#include <vector>
#include <io.h>
#include <fcntl.h>

/**
 * @brief Normalize the source vector and store the result in the destination vector.
 * 
 * @param src The source vector to be normalized.
 * @param dst The destination vector to store the normalized result.
 * @param len The length of the vectors.
 * 
 * @see https://www.mathsisfun.com/algebra/vector-unit.html
 */
void NormalizeVector(float* src, float* dst, int len);

/**
 * @brief Add two vectors and store the result in another vector.
 * 
 * @param v1 The first vector to be added.
 * @param v2 The second vector to be added.
 * @param result The vector to store the result of the addition.
 * @param len The length of the vectors.
 * 
 * @see https://mathinsight.org/vector_introduction
 */
void AddVectors(float* v1, float* v2, float* result, int len);

/**
 * @brief Subtract one vector from another and store the result in another vector.
 * 
 * @param v1 The vector from which the other vector will be subtracted.
 * @param v2 The vector to be subtracted from the first vector.
 * @param result The vector to store the result of the subtraction.
 * @param len The length of the vectors.
 * 
 * @see https://mathinsight.org/vector_introduction
 */
void SubVectors(float* v1, float* v2, float* result, int len);

/**
 * @brief Calculate the dot product of two vectors.
 * 
 * @param u The first vector for the dot product.
 * @param v The second vector for the dot product.
 * @param len The length of the vectors.
 * @return The dot product of the two vectors.
 * 
 * @see https://www.mathsisfun.com/algebra/vectors-dot-product.html
 */
float DotVectors(float* u, float* v, int len);

/**
 * @brief Calculate the cross product of two vectors and store the result in another vector.
 * 
 * @param u The first vector for the cross product.
 * @param v The second vector for the cross product.
 * @param result The vector to store the result of the cross product.
 * 
 * @see https://kids.kiddle.co/Cross_product
 */
void CrossProduct(float* u, float* v, float* result);

/**
 * @brief Scale a vector by a given factor.
 * 
 * @param v The vector to be scaled.
 * @param scale The scaling factor.
 * @param len The length of the vector.
 * 
 * @see https://mathinsight.org/vector_introduction
 */
void ScaleVector(float* v, float scale, int len);


