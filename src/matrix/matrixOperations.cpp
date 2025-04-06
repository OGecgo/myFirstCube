#include "./headers/matrixOperations.hpp"

#include <cstdlib>


float* returnMultiplyMatrix4x4_4x4(float* matrix1, float* matrix2){
    float* newMatrix = (float*)malloc(sizeof(float) * 16);

    for (int i = 0; i < 4; i ++){ //x y z w
        newMatrix[i * 4]     = matrix1[i * 4] * matrix2[0] + matrix1[i * 4 + 1] * matrix2[4] + matrix1[i * 4 + 2] * matrix2[8] +  matrix1[i * 4 + 3] * matrix2[12];
        newMatrix[i * 4 + 1] = matrix1[i * 4] * matrix2[1] + matrix1[i * 4 + 1] * matrix2[5] + matrix1[i * 4 + 2] * matrix2[9] +  matrix1[i * 4 + 3] * matrix2[13];
        newMatrix[i * 4 + 2] = matrix1[i * 4] * matrix2[2] + matrix1[i * 4 + 1] * matrix2[6] + matrix1[i * 4 + 2] * matrix2[10] + matrix1[i * 4 + 3] * matrix2[14];
        newMatrix[i * 4 + 3] = matrix1[i * 4] * matrix2[3] + matrix1[i * 4 + 1] * matrix2[7] + matrix1[i * 4 + 2] * matrix2[11] + matrix1[i * 4 + 3] * matrix2[15];
    }

    return newMatrix;
}
float* returnMultiplyMatrix4x4_4x1(float* matrix1, float* matrix2){
    float* newMatrix = (float*)malloc(sizeof(float) * 4);
    // x y z w
    newMatrix[0] = matrix1[0]  * matrix2[0] + matrix1[1]  * matrix2[1] + matrix1[2]  * matrix2[2] + matrix1[3]  * matrix2[3];
    newMatrix[1] = matrix1[4]  * matrix2[0] + matrix1[5]  * matrix2[1] + matrix1[6]  * matrix2[2] + matrix1[7]  * matrix2[3];
    newMatrix[2] = matrix1[8]  * matrix2[0] + matrix1[9]  * matrix2[1] + matrix1[10] * matrix2[2] + matrix1[11] * matrix2[3];
    newMatrix[3] = matrix1[12] * matrix2[0] + matrix1[13] * matrix2[1] + matrix1[14] * matrix2[2] + matrix1[15] * matrix2[3];
        
    return newMatrix;
}