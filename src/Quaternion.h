#pragma once

/**
 * @brief A struct for Quaternion in 3D space
 * 
 * @see https://www.3dgep.com/understanding-quaternions/
 */
struct Quaternion {
    float w; 
    float x;
    float y; 
    float z;

    void _Init_(float w, float x, float y, float z);
    Quaternion Reciprocal();
    Quaternion Conjugation();
    void Normalize();

};

/**
 * @brief Compute the Hamilton product of two quaternions.
 * 
 * @param q1 The first quaternion.
 * @param q2 The second quaternion.
 * @return The result of the Hamilton product.
 * 
 * @see http://aleph0.clarku.edu/~ma130/quaternions.pdf
 */
Quaternion HamiltonProduct(const Quaternion& q1, const Quaternion& q2);

/**
 * @brief Rotate a 3D vector using a quaternion.
 * 
 * @param q The rotation quaternion.
 * @param src The source vector to be rotated.
 * @param dst The destination vector to store the rotated result.
 * 
 * @see https://graphics.stanford.edu/courses/cs348a-17-winter/Papers/quaternion.pdf
 */
void QuaternionRotate(const Quaternion& q, const float* src, float* dst);

/**
 * @brief Compute the dot product of two quaternions.
 * 
 * @param q1 The first quaternion.
 * @param q2 The second quaternion.
 * @return The dot product of the two quaternions.
 * 
 * @see https://www.mathsisfun.com/algebra/vector-unit.html
 */
float QuaternionDot(const Quaternion& q1, const Quaternion& q2);

/**
 * @brief Perform spherical linear interpolation (SLERP) between two quaternions.
 * 
 * @param q1 The first quaternion.
 * @param q2 The second quaternion.
 * @param t Interpolation parameter.
 * @return The result of the spherical linear interpolation.
 * 
 * @see https://splines.readthedocs.io/en/latest/rotation/slerp.html
 */
Quaternion QuaternionSlerp(const Quaternion& q1, const Quaternion& q2, float t);
