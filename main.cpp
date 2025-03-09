#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

#include "myVector.hpp"
#include "draw.hpp"

#define clrscr(){ system("@cls||clear"); }
#define xSize 100
#define ySize 50
#define FOV 90
#define zFar 1000
#define zNear 0.1


void RotateX(std::vector<float*>& face){
    addMatrix(face, callTransformations(0, 0.22, 0.02));
    multiplyMatrix(face, callRotateX(0.2));
}

void RotateY(std::vector<float*>& face){
    addMatrix(face, callTransformations(0.22, 0, 0.02));
    multiplyMatrix(face, callRotateY(0.2));
}

void RotateZ(std::vector<float*>& face){
    //addMatrix(face, callTransformations(0, 0, 0));
    multiplyMatrix(face, callRotateZ(0.2));
}


 

int main() {  
    clrscr();
    
    // cordinations cube
    float size = 0.5;
    float s = 0.5;
    float sd = s + 0.25;
    int time = 1000 * 200;
    //x, y, z, w
    float pos1[4] = { -size,  -size,  s, 1};
    float pos2[4] = {  size,  -size,  s, 1};
    float pos3[4] = {  size, size,  s, 1};
    float pos4[4] = { -size, size,  s, 1};

    // float pos5[4] = { -size,  -size,  sd, 1};
    // float pos6[4] = {  size,  -size,  sd, 1};
    // float pos7[4] = {  size, size,  sd, 1};
    // float pos8[4] = { -size, size,  sd, 1};
    
    std::vector<float*> face = {pos1, pos2, pos3, pos4};//, pos5, pos6, pos7, pos8};//, pos5, pos6, pos7, pos8};
    multiplyMatrix(face, callProjMatrix(xSize, ySize, FOV, zNear, zFar));

    while (true) {
        // Convert positions and draw
        std::vector<int*> draw = convertPositions(face, xSize, ySize);
        drawCube(draw);
        drawScreen(draw, xSize, ySize);

        RotateX(face);

        usleep(time);
        draw.clear();
    }

    return 0; 
}