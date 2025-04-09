#include "./res/header/reedObj.hpp"

#include "./src/matrix/header/myConverts.hpp"
#include "./src/matrix/header/transformation.hpp"

#include "./src/window/header/render.hpp"
#include "./src/window/header/keyControler.hpp"

#include <stdio.h>
#include <vector>

#define sizePixel 4
#define xSizeScreen 1200 / sizePixel //75
#define ySizeScreen 800 / sizePixel //50
#define FOV 90

#define zFar 1000
#define zNear 1
//--------Print
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
//--------Clear
void clearVector(std::vector<float*>& vec){
    for(float* item: vec){
        free(item);
    }
    vec.clear();
}
void clearVector(std::vector<int*>& vec){
    for(int* item: vec){
        free(item);
    }
    vec.clear();
}

int main(){ 

    //initialize positions
    //const char* path = "./res/txtFiles/vectorPos.txt";
    const char* path = "./res/Models/cube.obj";
    std::vector<int*> vectorPosInt;
    std::vector<float*> vectorPos;
    std::vector<float*> normilizedPos;

    myConverts* c;
    reedObj* obj = new reedObj(path);

    //test
    c = new myConverts(xSizeScreen, ySizeScreen, FOV, zFar, zNear);
    vectorPos = c->addDimentionW(obj->getVertex());
    printVector(vectorPos, 4);

    // //normilize unit
    // vectorPos = c->returnNormalizedUnitRange(vectorPosInt);
    // clearVector(vectorPosInt);
    // //printVector(vectorPos, 4);


    // // //render
    int red = 0;
    int green = 0;
    int blue = 0;
    render* r = new render(xSizeScreen, ySizeScreen, sizePixel, red, green, blue);
    while (!windowClosed()){
        //transforamtion
        for (int pos = 0; pos < vectorPos.size(); pos++){
            float* item = returnRotateZ(vectorPos[pos], 3);
            free(vectorPos[pos]);
            vectorPos[pos] = item;
        }

        //normilize and take positions
        normilizedPos = c->returnNormalizedPos(vectorPos);
        clearVector(vectorPosInt);
        vectorPosInt = c->returnPosScreen(normilizedPos);
        clearVector(normilizedPos);
        //printVector(vectorPosInt, 2);

        r->makeFrame(vectorPosInt);
        r->delay(200);        
    }

    //end
    clearVector(normilizedPos);
    clearVector(vectorPosInt);
    clearVector(vectorPos);  
    
    delete r;
    delete c;
    return 0;    
}