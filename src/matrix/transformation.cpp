
#include "./header/matrixOperations.hpp"

#include <cstdlib>
#include <cmath>


float* returnMove(float* matrixPos, float x, float y, float z){
    float* move = new float[16]{
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1  
    };
    float* newMatrix = returnMultiplyMatrix4x4_4x1(move, matrixPos);
    free(move);
    return newMatrix;
}
float* returnRotateX(float* matrixPos, float angle){
    float* move = new float[16]{
        1, 0          , 0           , 0,
        0, cosf(angle), -sinf(angle), 0,
        0, sinf(angle), cosf(angle) , 0,
        0, 0          , 0           , 1  
    };
    float* newMatrix = returnMultiplyMatrix4x4_4x1(move, matrixPos);
    free(move);
    return newMatrix;
}
float* returnRotateY(float* matrixPos, float angle){
    float* move = new float[16]{
        cosf(angle) , 0, sinf(angle), 0,
        0           , 1, 0          , 0,
        -sinf(angle), 0, cosf(angle), 0,
        0           , 0, 0          , 1  
    };
    float* newMatrix = returnMultiplyMatrix4x4_4x1(move, matrixPos);
    free(move);
    return newMatrix;
}
float* returnRotateZ(float* matrixPos, float angle){
    float* move = new float[16]{
        cosf(angle) , sinf(angle), 0, 0,
        -sinf(angle), cosf(angle), 0, 0,
        0           , 0          , 1, 0,
        0           , 0          , 0, 1  
    };
    float* newMatrix = returnMultiplyMatrix4x4_4x1(move, matrixPos);
    free(move);
    return newMatrix;
}