
#include <iostream>
#include <math.h>

#include "Vector.h"

// u = U / ∣U∣
// ∣U∣ = SquareRoot(X^2 + Y2 + Z2)
void NormalizeVector(float* src, float* dst, int len){
    int length = 0;
    
    for(size_t i = 0; i < len; i++){
        length += src[i] * dst[i];
    }

    length = (length);

    for(size_t i = 0; i < len; i++){
        dst[i] = src[i] / length;
    }
}

// u + v = <u1, u2, v1, v2> 
void AddVectors(float* v1, float* v2, float* result, int len){
    for(size_t i = 0; i < len; i++){
        result[i] = v1[i] + v2[i];
    }  
}

// u - v = <u1, u2, v1, v2> 
void SubVectors(float* v1, float* v2, float* result, int len){
    for(size_t i = 0; i < len; i++){
        result[i] = v1[i] - v2[i];
    }
}


float DotVectors(float* u, float* v, int len){
    float sum = 0;
    for(size_t i = 0; i < len; i++){
        sum += u[i] * v[i];
    }
    return sum;
}


void CrossProduct(float* u, float* v, float* result){
    float resultX = (u[1] * v[2]) - (u[2] * v[1]); // no X i.e [0]
    float resultY = (u[0] * v[2]) - (u[2] * v[0]); // no Y i.e [1]
    float resultZ = (u[0] * v[1]) - (u[1] * v[0]); // no X i.e [2]

    result[0] = resultX;
    result[1] = resultY;
    result[2] = resultZ;
}


void ScaleVector(float* v, float scale, int len){
    for(size_t i = 0; i < len; i++){
        v[i] = v[i] * scale;
        printf("scale %f\n", scale);
    }
}

