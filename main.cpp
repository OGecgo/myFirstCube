#include "./res/headers/readTxt.hpp"
#include "./src/matrix/header/myConverts.hpp"

#include <stdio.h>
#include <vector>

#define xSizeScreen 1200//75
#define ySizeScreen 800//50
#define FOV 90

#define zFar 1000
#define zNear 1

void printVector(const std::vector<int*>& vec, int sizeInt) {
    
    printf("vec < ");
    for (int* items: vec) {
        printf("[");
        for (int i = 0; i < sizeInt - 1; i++){
            printf("%d, ", items[i]);    
        }
        printf("%d", items[sizeInt -1]);
        printf("] ");
    }
    printf(">\n");
}

void printVector(const std::vector<float*>& vec, int sizeInt) {
    
    printf("vec < ");
    for (float* items: vec) {
        printf("[");
        for (int i = 0; i < sizeInt - 1; i++){
            printf("%f, ", items[i]);    
        }
        printf("%f", items[sizeInt -1]);
        printf("] ");
    }
    printf(">\n");
}

int main(){ 

    //run file is on root Cube
    const char* path = "./res/txtFiles/vectorPos.txt";
    std::vector<int*> vectorPosInt = returnVectorIntArrayFromTxt(path, 4); // no 1 to -1 but 1000 to -1000 and then make 1000 => 1
    printVector(vectorPosInt, 4);

    myConverts* c = new myConverts(xSizeScreen, ySizeScreen, FOV, zFar, zNear);

    std::vector<float*> vectorPos = c->returnNormalizedUnitRange(vectorPosInt);
    printVector(vectorPos, 4);

    vectorPosInt.clear();
    std::vector<float*> normilizedPos = c->returnNormalizedPos(vectorPos);
    printVector(normilizedPos, 4);
    vectorPosInt = c->returnPosScreen(normilizedPos);
    printVector(vectorPosInt, 2);

}