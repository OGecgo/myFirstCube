#include "./header/myConverts.hpp"
#include "./header/matrixOperations.hpp"

#include <cstdlib>


#include <cmath>
#define PI 3.141519
float* returnProjMatrix(int xSizeScrean, int ySizeScrean, float FOV, float zNear, float zFar){
    float aspectRatio = (float)xSizeScrean / (float)ySizeScrean;
    float fovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * PI);
    float zRange = zNear - zFar;

    float* projMatrix = (float*)malloc(4 * 4 * sizeof(float));
    projMatrix[0]  = fovRad / aspectRatio; projMatrix[1]  = 0;                    projMatrix[2]  = 0;                            projMatrix[3] = 0;
    projMatrix[4]  = 0;                    projMatrix[5]  = 1 / aspectRatio;      projMatrix[6]  = 0;                            projMatrix[7] = 0;
    projMatrix[8]  = 0;                    projMatrix[9]  = 0;                    projMatrix[10] = (zFar + zNear) / zRange;      projMatrix[11] = (2 * zFar * zNear) / zRange;
    projMatrix[12] = 0;                    projMatrix[13] = 0;                    projMatrix[14] = -1;                           projMatrix[15] = 0;

    return projMatrix;
}
     
myConverts::myConverts(int xSizeScreen, int ySizeScreen, float FOV, float zNear, float zFar){
    this->xSizeScreen = xSizeScreen;
    this->ySizeScreen = ySizeScreen;
    this->FOV = FOV;
    this->zFar = zFar;
    this->zNear = zNear;
    this->projMatrix = returnProjMatrix(xSizeScreen, ySizeScreen, FOV, zNear, zFar);
}  

myConverts::~myConverts(){
    if (this->projMatrix != NULL) {
        free(this->projMatrix);
        this->projMatrix = NULL;
    }
}
int myConverts::getXSizeScreen() { return this->xSizeScreen; }
int myConverts::getYSizeScreen() { return this->ySizeScreen; }
float myConverts::getFOV() { return this->FOV; }
float myConverts::getZNear() { return this->zNear; }
float myConverts::getZFar() { return this->zFar; }
float* myConverts::getProjMatrix() { return this->projMatrix; }

void myConverts::setXSizeScreen(int xSizeScreen) { this->xSizeScreen = xSizeScreen; }
void myConverts::setYSizeScreen(int ySizeScreen) { this->ySizeScreen = ySizeScreen; }
void myConverts::setFOV(float FOV) { this->FOV = FOV; }
void myConverts::setZNear(float zNear) { this->zNear = zNear; }
void myConverts::setZFar(float zFar) { this->zFar = zFar; }
void myConverts::setProjMatrix(float* projMatrix) {
    if (this->projMatrix != nullptr) {
        free(this->projMatrix);
    }
    this->projMatrix = projMatrix;
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

