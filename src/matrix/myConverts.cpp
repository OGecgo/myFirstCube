#include "./header/myConverts.hpp"
#include "./header/matrixOperations.hpp"
#include "../../res/headers/myMatrix.hpp"

#include <cstdlib>

     
myConverts::myConverts(int xSizeScreen, int ySizeScreen, float FOV, float zNear, float zFar){
    this->xSizeScreen = xSizeScreen;
    this->ySizeScreen = ySizeScreen;
    this->FOV = FOV;
    this->zFar = zFar;
    this->zNear = zNear;
    this->projMatrix = returnProjMatrix(xSizeScreen, ySizeScreen, FOV, zNear, zFar);
}  

myConverts::~myConverts(){
    free(this->projMatrix);
}


std::vector<float*> myConverts::returnNormalizedUnitRange(std::vector<int*> pos){
    std::vector<float*> newPos;
    for (int* item: pos){
        float* arrayOfFloats = (float*)malloc(sizeof(float) * 4);
        for(int i = 0; i < 3; i++){
            arrayOfFloats[i] = item[i] / 100000.0; // x y z
        }
        arrayOfFloats[3] = item[3]; // w 
        newPos.push_back(arrayOfFloats);
    }

    return newPos;
}

std::vector<float*> myConverts::returnNormalizedPos(std::vector<float*> pos){
    std::vector<float*> normalizedPos;
    for (float* item: pos){
        float* matrix = returnMultiplyMatrix4x4_4x1(this->projMatrix, item);
        if (matrix[3] != 0){
            matrix[0] /= matrix[3];
            matrix[1] /= matrix[3];
            matrix[2] /= matrix[3];
            matrix[3] = 1;
        }
        normalizedPos.push_back(matrix);
    }
    return normalizedPos;
}

std::vector<int*> myConverts::returnPosScreen(std::vector<float*> pos){
    std::vector<int*> Screen;
    for (int i = 0; i < pos.size(); i++) {
        float x = pos[i][0];
        float y = pos[i][1];
            
        // Convert to screen position where the middle position is 0
        int screenX = (int)((1 - x) * (xSizeScreen / 2.0));
        int screenY = (int)((1 - y) * (ySizeScreen / 2.0));

        //set value
        int* newPos = (int*)malloc(sizeof(int) * 2);
        newPos[0] = screenX;
        newPos[1] = screenY;
        Screen.push_back(newPos);
    }
    return Screen;
}

