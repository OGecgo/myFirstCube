#include "myMatrix.hpp"

#include <stdio.h>
#include <cmath>

#define PI 3.14159

#define left -1
#define right 1
#define up -2
#define down 2

void printVector(std::vector<float*> vec){
    for (int i = 0; i < vec.size(); i++){
        printf("%f, %f, %f, %f\n", vec[i][0], vec[i][1], vec[i][2], vec[i][3]);
    }

}



float* callProjMatrix(int xSize, int ySize, float FOV, float zNear, float zFar) {
    float a = ( ((float)ySize / (float)xSize)) / tanf(FOV / 2.0 / 180 * PI);
    float b = 1 / tanf(FOV / 2.0 / 180 * PI);
    float c = (float)zFar/(zFar - zNear);
    float d = (float)(-zFar * zNear)/(zFar - zNear);

    float* projMatrix = (float*)malloc(4 * 4 * sizeof(float));
    projMatrix[0] = a;  projMatrix[1] = 0;  projMatrix[2] = 0;  projMatrix[3] = 0;
    projMatrix[4] = 0;  projMatrix[5] = b;  projMatrix[6] = 0;  projMatrix[7] = 0;
    projMatrix[8] = 0;  projMatrix[9] = 0;  projMatrix[10] = c; projMatrix[11] = d;
    projMatrix[12] = 0; projMatrix[13] = 0; projMatrix[14] = -1; projMatrix[15] = 0;
    return projMatrix;
}


float* callTransformations(float X, float Y, float Z){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = 1;  matrix[1] = 0;  matrix[2] = 0;  matrix[3] = X;
    matrix[4] = 0;  matrix[5] = 1;  matrix[6] = 0;  matrix[7] = Y;
    matrix[8] = 0;  matrix[9] = 0;  matrix[10] = 1; matrix[11] = Z;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
    return matrix; 
}

//rotate around the midle of cordinates not midle of object
float* callRotateX(float angle){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = 1;  matrix[1] = 0;            matrix[2] = 0;             matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = cosf(angle);  matrix[6] = -sinf(angle);  matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = sinf(angle);  matrix[10] = cosf(angle);  matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0;           matrix[14] = 0;            matrix[15] = 1;
    return matrix; 
}

float* callRotateY(float angle){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = cosf(angle);  matrix[1] = 0;  matrix[2] = sinf(angle);  matrix[3] = 0;
    matrix[4] = 0;            matrix[5] = 1;  matrix[6] = 0;            matrix[7] = 0;
    matrix[8] = -sinf(angle); matrix[9] = 0;  matrix[10] = cosf(angle); matrix[11] = 0;
    matrix[12] = 0;           matrix[13] = 0; matrix[14] = 0;           matrix[15] = 1;
    return matrix; 
}

float* callRotateZ(float angle){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = cosf(angle);  matrix[1] = sinf(angle); matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = -sinf(angle); matrix[5] = cosf(angle); matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;            matrix[9] = 0;           matrix[10] = 1; matrix[11] = 0;
    matrix[12] = 0;           matrix[13] = 0;          matrix[14] = 0; matrix[15] = 1;
    return matrix; 
}

void BresenhamLineAlgorithm(std::vector<int*>& vec, int* pos1, int* pos2) {
    // positions
    int x1 = pos1[0], y1 = pos1[1];
    int x2 = pos2[0], y2 = pos2[1];
    
    //distance
    int dx = abs(x2 - x1), dy = abs(y2 - y1);

    //direction 
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    //err and e2 to understan if i need to move pixel or not
    int err = dx - dy;

    //add value
    int* posN = (int*)malloc(sizeof(int) * 2);
    posN[0] = x1;
    posN[1] = y1;
    vec.push_back(posN);
    //printf("Added position: (%d, %d)\n", x1, y1); // Debug print

    // sub x1 and y1 until they equal to startPositions
    while (x1 != x2 || y1 != y2) {

        // addition when e2 is cose to 0
        int e2 = 2 * err;
        // a * dy < dx when a is odd
        // if line more close to next pixely
        if (e2 > -dy) {
            //move err to next pixel y
            err -= dy;
            x1 += sx;
        }
        //a * dx < dy when a in odd.s
        //if line more close to bext pixel x
        if (e2 < dx) {
            //move err to next pixel x
            err += dx;
            y1 += sy;
        }
        //add value
        int* posN = (int*)malloc(sizeof(int) * 2);
        posN[0] = x1;
        posN[1] = y1;
        vec.push_back(posN);
        //printf("Added position: (%d, %d)\n", x1, y1); // Debug print
    }
}

// [x, y, z, w][a, b, c, d]
//             [a, b, c, d]
//             [a, b, c, d]
//             [a, b, c, d]
void multiplyMatrixPos4x1_4x4(float* Matrix, std::vector<float*>& Pos){

    for (int i = 0; i < Pos.size(); i++) {
        // float x = Pos[i][0] * Matrix[0] + Pos[i][1] * Matrix[4] + Pos[i][2] * Matrix[8] + Pos[i][3] * Matrix[12];
        // float y = Pos[i][0] * Matrix[1] + Pos[i][1] * Matrix[5] + Pos[i][2] * Matrix[9] + Pos[i][3] * Matrix[13];
        // float z = Pos[i][0] * Matrix[2] + Pos[i][1] * Matrix[6] + Pos[i][2] * Matrix[10] + Pos[i][3] * Matrix[14];
        // float w = Pos[i][0] * Matrix[3] + Pos[i][1] * Matrix[7] + Pos[i][2] * Matrix[11] + Pos[i][3] * Matrix[15];
        
        float x = Matrix[0] * Pos[i][0] + Matrix[1] * Pos[i][1] + Matrix[2] * Pos[i][2] + Matrix[3] * Pos[i][3];
        float y = Matrix[4] * Pos[i][0] + Matrix[5] * Pos[i][1] + Matrix[6] * Pos[i][2] + Matrix[7] * Pos[i][3];
        float z = Matrix[8] * Pos[i][0] + Matrix[9] * Pos[i][1] + Matrix[10] * Pos[i][2] + Matrix[11] * Pos[i][3];
        float w = Matrix[12] * Pos[i][0] + Matrix[13] * Pos[i][1] + Matrix[14] * Pos[i][2] + Matrix[15] * Pos[i][3];
        
        //PerspectiveDivision
        if (w != 0) {
            x /= w;
            y /= w;
            z /= w;
            w = 1;
        }
        //set value
        Pos[i][0] = x;
        Pos[i][1] = y;
        Pos[i][2] = z;
        Pos[i][3] = w;

        //debug print
        //printf("3D Position: (%f, %f, %f, %f)\n", Pos[i][0], Pos[i][1], Pos[i][2], Pos[i][3]);
    }
    free(Matrix);
}

void multiplyMatrix4x4(float* &matrix1, float* matrix2){

    for (int i = 0; i < 4; i ++){
        float x = matrix1[i * 4] * matrix2[0] + matrix1[i * 4 + 1] * matrix2[4] + matrix1[i * 4 + 2] * matrix2[8] +  matrix1[i * 4 + 3] * matrix2[12];
        float y = matrix1[i * 4] * matrix2[1] + matrix1[i * 4 + 1] * matrix2[5] + matrix1[i * 4 + 2] * matrix2[9] +  matrix1[i * 4 + 3] * matrix2[13];
        float z = matrix1[i * 4] * matrix2[2] + matrix1[i * 4 + 1] * matrix2[6] + matrix1[i * 4 + 2] * matrix2[10] + matrix1[i * 4 + 3] * matrix2[14];
        float w = matrix1[i * 4] * matrix2[3] + matrix1[i * 4 + 1] * matrix2[7] + matrix1[i * 4 + 2] * matrix2[11] + matrix1[i * 4 + 3] * matrix2[15];
        
        //set value
        matrix1[i * 4] = x;
        matrix1[i * 4 + 1] = y;
        matrix1[i * 4 + 2] = z;
        matrix1[i * 4 + 3] = w;
    }

    free(matrix2);
}

std::vector<int*> convertPositions(std::vector<float*> Pos, int xSize, int ySize){
    std::vector<int*> result;
    for (int i = 0; i < Pos.size(); i++) {
        float x = Pos[i][0];
        float y = Pos[i][1];

        // Convert to screen position where the middle position is 0
        int screenX = (int)((x + 1) * (xSize / 2.0));
        int screenY = (int)((1 + y) * (ySize / 2.0));
        
            
        // Debug print
        //printf("2D Position: (%d, %d)\n", screenX, screenY);
        
        //set value
        int* newPos = (int*)malloc(sizeof(int) * 2);
        newPos[0] = screenX;
        newPos[1] = screenY;
        result.push_back(newPos);
    }
    return result;
}



