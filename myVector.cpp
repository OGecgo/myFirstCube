#include "myVector.hpp"

#include <stdio.h>
#include <cmath>

#define PI 3.14159

#define left -1
#define right 1
#define up -2
#define down 2


float* callProjMatrix(int xSize, int ySize, int FOV, int zNear, int zFar){
    // if give ctg(FOV/2) they going to infinity for FOV -> 0 and 0 if FOV -> 180 
    //with that i can work with perspective
    //matrix
    float a = ((float)ySize / (float)xSize) * 1 / tanf(FOV / 2.0 / 180 * PI);// ctg(FOV / 2) == tanf(FOV / 2.0 / 180 * PI)
    float b = ((float)ySize / (float)xSize) * 1 / tanf(FOV / 2.0 / 180 * PI);
    float c = (float)zFar/(zFar - zNear); //more close to user screen more c -> 1
    float d = (float)(-zFar * zNear)/(zFar - zNear); //more close to user screen more d -> 0

    float* projMatrix = (float*)malloc(4 * 4 * sizeof(float));
    projMatrix[0] = a;  projMatrix[1] = 0;  projMatrix[2] = 0;  projMatrix[3] = 0;
    projMatrix[4] = 0;  projMatrix[5] = b;  projMatrix[6] = 0;  projMatrix[7] = 0;
    projMatrix[8] = 0;  projMatrix[9] = 0;  projMatrix[10] = c; projMatrix[11] = 1;
    projMatrix[12] = 0; projMatrix[13] = 0; projMatrix[14] = d; projMatrix[15] = 0;
    return projMatrix;
}

float* callTransformations(float X, float Y, float Z){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = X;  matrix[1] = 0;  matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = Y;  matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = 0;  matrix[10] = Z; matrix[11] = 1;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 0;
    return matrix; 
}

//rotate around the midle of cordinates not midle of object
float* callRotateX(float angle){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = 1;  matrix[1] = 0;            matrix[2] = 0;             matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = cosf(angle);  matrix[6] = sinf(angle);   matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = -sinf(angle); matrix[10] = cosf(angle);  matrix[11] = 1;
    matrix[12] = 0; matrix[13] = 0;           matrix[14] = 0;            matrix[15] = 0;
    return matrix; 
}

float* callRotateY(float angle){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = cosf(angle);  matrix[1] = 0;  matrix[2] = sinf(angle);  matrix[3] = 0;
    matrix[4] = 0;            matrix[5] = 1;  matrix[6] = 0;            matrix[7] = 0;
    matrix[8] = -sinf(angle); matrix[9] = 0;  matrix[10] = cosf(angle); matrix[11] = 1;
    matrix[12] = 0;           matrix[13] = 0; matrix[14] = 0;           matrix[15] = 0;
    return matrix; 
}

float* callRotateZ(float angle){
    float* matrix = (float*)malloc(4 * 4 * sizeof(float));
    matrix[0] = cosf(angle); matrix[1] = -sinf(angle); matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = sinf(angle); matrix[5] = cosf(angle);  matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;           matrix[9] = 0;            matrix[10] = 1; matrix[11] = 1;
    matrix[12] = 0;          matrix[13] = 0;           matrix[14] = 0; matrix[15] = 0;
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

void addMatrix(std::vector<float*>& face, float* Matrix){
    // addition face amd matrix [a11, a22, a33 a44] from Matrix
    for (int i = 0; i < face.size(); i++) {
        float x = face[i][0] + Matrix[0];
        float y = face[i][1] + Matrix[5];
        float z = face[i][2] + Matrix[10];
        float w = face[i][3] + Matrix[15];

        //set value
        face[i][0] = x;
        face[i][1] = y;
        face[i][2] = z;
        face[i][3] = w;

        //debug print
        //printf("3D Position: (%f, %f, %f, %f)\n", face[i][0], face[i][1], face[i][2], face[i][3]);
    }
}

void multiplyMatrix(std::vector<float*>& face, float* Matrix){

    for (int i = 0; i < face.size(); i++) {
        float x = face[i][0] * Matrix[0] + face[i][1] * Matrix[4] + face[i][2] * Matrix[8] + face[i][3] * Matrix[12];
        float y = face[i][0] * Matrix[1] + face[i][1] * Matrix[5] + face[i][2] * Matrix[9] + face[i][3] * Matrix[13];
        float z = face[i][0] * Matrix[2] + face[i][1] * Matrix[6] + face[i][2] * Matrix[10] + face[i][3] * Matrix[14];
        float w = face[i][0] * Matrix[3] + face[i][1] * Matrix[7] + face[i][2] * Matrix[11] + face[i][3] * Matrix[15];
        
        //printf("%f\n", w);
        if (w != 0) {
            x /= w;
            y /= w;
            z /= w;
        }
        //set value
        face[i][0] = x;
        face[i][1] = y;
        face[i][2] = z;
        face[i][3] = w;

        //debug print
        //printf("3D Position: (%f, %f, %f, %f)\n", face[i][0], face[i][1], face[i][2], face[i][3]);
    }
    // Debug print for face and matrix
    // printf("Face: (x%f, y%f, z%f, w%f)\n", face[0][0], face[0][1], face[0][2], face[0][3]);
    // printf("Matrix: z(x%f, y%f, z%f, w%f)\n", Matrix[2] * face[0][0], Matrix[6] * face[0][1], Matrix[10], Matrix[14]);
}

std::vector<int*> convertPositions(std::vector<float*> face, int xSize, int ySize){
    std::vector<int*> result;
    for (int i = 0; i < face.size(); i++) {
        float x = face[i][0];
        float y = face[i][1];

        // Convert to screen position where the middle position is 0
        int screenX = (int)((x + 1) * (xSize / 2.0));
        int screenY = (int)((1 - y) * (ySize / 2.0));
        
        
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



