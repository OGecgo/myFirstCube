#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

#include "myVector.hpp"
#include "draw.hpp"

#define clrscr(){ system("@cls||clear"); }
#define xSize 75
#define ySize 50
#define FOV 90
#define zFar 1000
#define zNear 1

void RotateX(std::vector<float*>& face) {
    float* moveToCenter = callTransformations(-0, -0, -0.8);
    float* moveBack = callTransformations(0, 0, 0.8);

    multiplyMatrix(face, moveToCenter);  // got to center of map
    multiplyMatrix(face, callRotateX(0.2)); // rotate
    multiplyMatrix(face, moveBack);  // go back to position
}

void RotateY(std::vector<float*>& face) {
    float* moveToCenter = callTransformations(-0, -0, -1.25);
    float* moveBack = callTransformations(0, 0, 1.25);

    multiplyMatrix(face, moveToCenter);  // got to center of map
    multiplyMatrix(face, callRotateY(0.2)); // rotate
    multiplyMatrix(face, moveBack);  // go back to position
}

void RotateZ(std::vector<float*>& face){
    float* moveToCenter = callTransformations(-0, -0, -0.8);
    float* moveBack = callTransformations(0, 0, 0.8);

    multiplyMatrix(face, moveToCenter);  // got to center of map
    multiplyMatrix(face, callRotateZ(0.2)); // rotate
    multiplyMatrix(face, moveBack);  // go back to position}
}

int main() {  
    clrscr();

    float z1 = 1;
    float z2 = 1.5;
    
    // Coordinates for the cube
    float pos1[4] = { -0.5, -0.5, z1, 1};
    float pos2[4] = {  0.5, -0.5, z1, 1};
    float pos3[4] = {  0.5,  0.5, z1, 1};
    float pos4[4] = { -0.5,  0.5, z1, 1};

    float pos5[4] = { -0.5, -0.5, z2, 1};
    float pos6[4] = {  0.5, -0.5, z2, 1};
    float pos7[4] = {  0.5,  0.5, z2, 1};
    float pos8[4] = { -0.5,  0.5, z2, 1};
    
    std::vector<float*> face = {pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8};
    multiplyMatrix(face, callProjMatrix(xSize, ySize, FOV, zNear, zFar));

    int time = 1000 * 100;

    while (true) {    
        std::vector<int*> draw = convertPositions(face, xSize, ySize);
        drawCube(draw);
        drawScreen(draw, xSize, ySize);
    
        RotateY(face);
    
        draw.clear();
        usleep(time);
    }

    return 0; 
}