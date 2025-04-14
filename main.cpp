#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>

#include "myMatrix.hpp"
#include "draw.hpp"

#define xSize 75
#define ySize 50
#define FOV 90

#define zFar 1000
#define zNear 1

void RotateX(std::vector<float*>& positions) {
    float* matrixMul = callTransformations(0, 0, 1.25);
    multiplyMatrix4x4(matrixMul, callRotateX(0.2));
    multiplyMatrix4x4(matrixMul, callTransformations(0, 0, -1.25));
    multiplyMatrixPos4x1_4x4(matrixMul, positions);

}

void RotateY(std::vector<float*>& positions) {
    float* matrixMul = callTransformations(0, 0, 1.25);
    multiplyMatrix4x4(matrixMul, callRotateY(0.2));
    multiplyMatrix4x4(matrixMul, callTransformations(0, 0, -1.25));
    multiplyMatrixPos4x1_4x4(matrixMul, positions);
}


void RotateZ(std::vector<float*>& positions){
    multiplyMatrixPos4x1_4x4(callRotateZ(0.2), positions);
}

int main() {  
    system("@cls||clear");
    printf("\x1b[H");

    //positions
    float z1 = 1;
    float z2 = 1.5;

    float xy1 = 0.5;
    float xy2 = 0.5;
    
    float pos1[4] = { -xy1, -xy1, z1, 1};
    float pos2[4] = {  xy1, -xy1, z1, 1};
    float pos3[4] = {  xy1,  xy1, z1, 1};
    float pos4[4] = { -xy1,  xy1, z1, 1};

    float pos5[4] = { -xy2, -xy2, z2, 1};
    float pos6[4] = {  xy2, -xy2, z2, 1};
    float pos7[4] = {  xy2,  xy2, z2, 1};
    float pos8[4] = { -xy2,  xy2, z2, 1};
    
    std::vector<float*> positions = {pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8};
    //normilize
    float* normilize = returnMultiplyMatrixPos4x1_4x4(callProjMatrix(xSize, ySize, FOV, zNear, zFar), positions);
    //time
    int time = 1000 * 100;

    while (true) {  
        
        //draw
        std::vector<int*> draw = convertPositions(normilize, positions.size(), xSize, ySize);
        drawCube(draw);
        drawScreen(draw, xSize, ySize);
        
        //covert positions
        RotateY(positions);

        //normilize
        free(normilize);
        normilize = returnMultiplyMatrixPos4x1_4x4(callProjMatrix(xSize, ySize, FOV, zNear, zFar), positions);


        //printf("\x1b[H");
        //printVector(positions);

        draw.clear();
        usleep(time);
    }

    return 0; 
}
