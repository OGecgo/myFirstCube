#include "draw.hpp"

#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include "myMatrix.hpp"

#define clrscr(){ system("@cls||clear"); }


void makeTringle(std::vector<int*>& vec, int* pos1, int* pos2, int* pos3){

    BresenhamLineAlgorithm(vec, pos1, pos2);
    BresenhamLineAlgorithm(vec, pos1, pos3);
    BresenhamLineAlgorithm(vec, pos2, pos3);
}

void drawFace(std::vector<int*>& vec, int* pos1, int* pos2, int* pos3, int* pos4){

    BresenhamLineAlgorithm(vec, pos1, pos2);
    BresenhamLineAlgorithm(vec, pos2, pos3);

    BresenhamLineAlgorithm(vec, pos3, pos4);
    BresenhamLineAlgorithm(vec, pos4, pos1);
}

void drawCube(std::vector<int*>& vec){
    drawFace(vec, vec[0], vec[1], vec[2], vec[3]); // Front face
    drawFace(vec, vec[4], vec[5], vec[6], vec[7]); // Back face
    drawFace(vec, vec[0], vec[1], vec[5], vec[4]); // Top face
    drawFace(vec, vec[2], vec[3], vec[7], vec[6]); // Bottom face
    drawFace(vec, vec[1], vec[2], vec[6], vec[5]); // Right face
    drawFace(vec, vec[0], vec[3], vec[7], vec[4]); // Left face

    // makeTringle(vec, vec[0], vec[1], vec[2]);//front face
    // makeTringle(vec, vec[1], vec[2], vec[3]);
    // makeTringle();//back face
    // makeTringle();
}

void drawCubewithDringle(std::vector<int*>& vec){

}

void drawScreen(std::vector<int*> draw, int xSize, int ySize){
    //draw
    printf("\x1b[H");
    printf("\n\n\n\n\n\n\n\n\n");
    //clrscr();  

    //screan
    for (int y = 0; y <= ySize; y++){
        for (int x = 0; x <= xSize; x++){
            //positions
            bool b = false; 
            for (int i = 0; i < draw.size(); i++){
                if(draw[i][0] == x && draw[i][1] == y) b = true;
            }
            if(b) printf(" ");
            else printf("@");
        }
        printf("\n");
    }
}
