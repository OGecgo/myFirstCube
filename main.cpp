#include <stdio.h>
#include <unistd.h>

#include <vector>

#include "myVector.cpp"
#include "draw.cpp"

#define clrscr(){ system("@cls||clear"); }
#define xSize 20
#define ySize 10




void makeTringle(std::vector<int*>* vec, int* pos1, int* pos2, int* pos3){

    setVectorLine(vec, pos1, pos2);
    setVectorLine(vec, pos1, pos3);
    setVectorLine(vec, pos2, pos3);
}

void drawFace(std::vector<int*>* vec, int* pos1, int* pos2, int* pos3, int* pos4){

    setVectorLine(vec, pos1, pos2);
    setVectorLine(vec, pos2, pos3);

    setVectorLine(vec, pos3, pos4);
    setVectorLine(vec, pos4, pos1);
}


int main() { 
    clrscr();
    
    // cordinations cube
    float size = 0.5;
    float pos1[4] = { -size,  -size,  0, 1};
    float pos2[4] = {  size,  -size,  0, 1};
    float pos3[4] = {  size, size,  0, 1};
    float pos4[4] = { -size, size,  0, 1};
    // float pos5[4] = { -size,  size, 0, 1};
    // float pos6[4] = {  size,  size, 0, 1};
    // float pos7[4] = {  size, -size, 0, 1};
    // float pos8[4] = { -size, -size, 0, 1};

    std::vector<float*> face = {pos1, pos2, pos3, pos4};//, pos5, pos6, pos7, pos8};
    std::vector<int*> draw = normilizePositions(face, xSize, ySize);  // Преобразуем 3D в 2D

    // Draw all six faces of the cube
    drawFace(&draw, draw[0], draw[1], draw[2], draw[3]); // Front face
    // drawFace(&draw, draw[4], draw[5], draw[6], draw[7]); // Back face
    // drawFace(&draw, draw[0], draw[1], draw[5], draw[4]); // Top face
    // drawFace(&draw, draw[2], draw[3], draw[7], draw[6]); // Bottom face
    // drawFace(&draw, draw[1], draw[2], draw[6], draw[5]); // Right face
    // drawFace(&draw, draw[0], draw[3], draw[7], draw[4]); // Left face
    //return 0;
    while (true) {
        drawScreen(draw, xSize, ySize);
        usleep(1000 * 1000);
    }

    return 0;
}