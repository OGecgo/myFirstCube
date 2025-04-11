#include "./header/myConverts.hpp"
#include "./header/matrixOperations.hpp"


     
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

std::vector<float*> myConverts::addDimentionW(std::vector<float*> pos){

    std::vector<float*> newPos;
    for(float* item: pos){
        float* newItem = new float[4];
        newItem[0] = item[0]; 
        newItem[1] = item[1]; 
        newItem[2] = item[2]; 
        newItem[3] = 1; 
        newPos.push_back(newItem);
    }
    return newPos;
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

