
#include <iostream>
#include <cmath>
#include <cassert>
//include <gtest/gtest.h>
#include "Quaternion.h"

#include <time.h>
#include <iostream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <vector>

const float C = 2.0f;

void Quaternion:: _Init_(float w, float x, float y, float z){
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion Quaternion::Conjugation(){
    Quaternion conjugation;
	conjugation.w = this->w;
	conjugation.x = -this->x;
	conjugation.y = -this->y;
	conjugation.z = -this->z;

	return conjugation;
}

void Quaternion:: Normalize(){
    
    float norm = std::sqrt(pow(this->w, C) + pow(this->x, C) + pow(this->y, C) + pow(this->w, z));
    this->w /= norm;
    this->x /= norm;
    this->y /= norm;
    this->z /= norm;
}

Quaternion Quaternion:: Reciprocal(){
    Quaternion conjugation = this->Conjugation();
    float norm = std::sqrt(pow(this->w, C) + pow(this->x, C) + pow(this->y, C) + pow(this->w, z));
    conjugation.w /= norm;
    conjugation.x /= norm;
    conjugation.y /= norm;
    conjugation.z /= norm;
}

Quaternion HamiltonProduct(Quaternion &q1, Quaternion&q2){
    Quaternion result; 

    result.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
    result.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
    result.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
    result.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);

    return result;
}

void QuaternionRotate(Quaternion *q, float* src, float *dst){
    Quaternion recip = q->Reciprocal();

	Quaternion qv;
	qv._Init_(0, src[0], src[1], src[2]);

	Quaternion temp = HamiltonProduct(*q, qv);
	temp = HamiltonProduct(temp, recip);

	dst[0] = temp.x;
	dst[1] = temp.y;
	dst[2] = temp.z;
}

float QuaternionDot(Quaternion *q1, Quaternion *q2){
    float ans = (q1->w * q2->w) + (q1->x * q2->x) + (q1->y * q2->y) + (q1->z * q2->z);
    return ans;
}

Quaternion QuaternionSlerp(Quaternion *q1, Quaternion *q2, float t){
    float dot = QuaternionDot(q1, q2);
    if(dot > 1.0) {dot = 1.0;}
    float theta = acos(dot);

    float sin_theta = sin(theta);
    float st = sin(t * theta);
    float st_minus_t = sin((1.0f - t) * theta);

    Quaternion q3; 
    q3.w = q1->w * (st_minus_t / sin_theta) + q2->w * (st / sin_theta);
	q3.x = q1->x * (st_minus_t / sin_theta) + q2->x * (st / sin_theta);
	q3.y = q1->y * (st_minus_t / sin_theta) + q2->y * (st / sin_theta);
	q3.z = q1->z * (st_minus_t / sin_theta) + q2->z * (st / sin_theta);

    return q3;
}


/*
TEST(QuaternionTest, HamiltonProduct) {
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);

    Quaternion result = HamiltonProduct(q1, q2);

    // Replace the expected values with the correct results
    ASSERT_FLOAT_EQ(result.w, expected_w);
    ASSERT_FLOAT_EQ(result.x, expected_x);
    ASSERT_FLOAT_EQ(result.y, expected_y);
    ASSERT_FLOAT_EQ(result.z, expected_z);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    printf("hello");
    return 0;
}*/