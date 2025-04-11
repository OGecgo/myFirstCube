#include "../Scene.hpp"

#include <cmath>
#include <cstdio>

#include "../Shapes.hpp"

#define PI 3.141519
#define isMapEnd(item) \   
    if (item == objs.end()) { \
        printf("Error: Object '%s' not found.\n", objName); \
        exit(1); \
    }
#define testPosVertes(item) \
    if (item->getRowSize() != 4 && item->getColumnSize() != 1){\
        printf("Error Vertex Pos: positions need to be row = 4 column = 1 [x , y, z, w]");\
        exit(1);\
    }


//constractor deconstractor
Scene::Scene(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar){
    this->xScreenSize = xScreenSize;
    this->yScreenSize = yScreenSize;
    this->FOV = FOV;
    this->zNear = zNear;
    this->setMyProjectionMatrix(returnNewProjectionMatrix(xScreenSize, yScreenSize, FOV, zNear, zFar));
}
Scene::~Scene(){
    if (this->projMatrix != NULL){
        delete[] this->projMatrix;
        this->projMatrix = NULL;
    }
    for (std::map<const char*, Obj*>::iterator item = objs.begin(); item != objs.end(); ++item){
        delete (*item).second;
        objs.erase(item);
    }
}

// add object to map
void Scene::openObj(const char* path){
    Obj* newObj = new Obj(path);
    char* name;
    int startPosName = 0;
    int sizeName = 0;
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '\\' || path[i] == '/'){
            startPosName = i;
        }
        if (path[i + 1] == '\0'){
            sizeName = i - startPosName;
            break;
        }
    }
    name = new char[sizeName];
    for (int i = startPosName; path[i] != '\0'; i++){
        name[i] = path[i];
    }
    objs.insert({name, newObj});   
}


//transformations
void Scene::moveObj(const char* objName, float x, float y, float z){
    std::map<const char*, Obj*>::iterator item = objs.find(objName);
    isMapEnd(item);
    Matrix* matrixMove = new Matrix(4, 4);
    matrixMove->setMatrixItem(0, 0, 1);
    matrixMove->setMatrixItem(1, 1, 1);
    matrixMove->setMatrixItem(2, 2, 1);

    matrixMove->setMatrixItem(3, 0, x);
    matrixMove->setMatrixItem(3, 1, y);
    matrixMove->setMatrixItem(3, 2, z);
    matrixMove->setMatrixItem(3, 3, 1);

    Obj* obj = (*item).second;
    obj->setGlobalPos((*(obj->getGlobalPos())) * matrixMove);
    matrixMove->~Matrix();
}

void Scene::rotateXObj(const char* objName, int angle){
    std::map<const char*, Obj*>::iterator item = objs.find(objName);
    isMapEnd(item);

    float radians = angle * PI / 180.0f; // Convert angle to radians
    Matrix* matrixRotateX = new Matrix(4, 4);
    matrixRotateX->setMatrixItem(0, 0, 1);
    matrixRotateX->setMatrixItem(1, 1, cos(radians));
    matrixRotateX->setMatrixItem(1, 2, -sin(radians));
    matrixRotateX->setMatrixItem(2, 1, sin(radians));
    matrixRotateX->setMatrixItem(2, 2, cos(radians));
    matrixRotateX->setMatrixItem(3, 3, 1);

    Obj* obj = (*item).second;
    obj->setGlobalPos((*(obj->getGlobalPos())) * matrixRotateX);
    matrixRotateX->~Matrix();
}
void Scene::rotateYObj(const char* objName, int angle){
    std::map<const char*, Obj*>::iterator item = objs.find(objName);
    isMapEnd(item);

    float radians = angle * PI / 180.0f; // Contvert angle to radians
    Matrix* matrixRotateY = new Matrix(4, 4);
    matrixRotateY->setMatrixItem(0, 0, cos(radians));
    matrixRotateY->setMatrixItem(0, 2, sin(radians));
    matrixRotateY->setMatrixItem(1, 1, 1);
    matrixRotateY->setMatrixItem(2, 0, -sin(radians));
    matrixRotateY->setMatrixItem(2, 2, cos(radians));
    matrixRotateY->setMatrixItem(3, 3, 1);

    Obj* obj = (*item).second;
    obj->setGlobalPos((*(obj->getGlobalPos())) * matrixRotateY);
    matrixRotateY->~Matrix();
}
void Scene::rotateZObj(const char* objName, int angle){
    std::map<const char*, Obj*>::iterator item = objs.find(objName);
    isMapEnd(item);

    float radians = angle * PI / 180.0f; // Convert angle to radians
    Matrix* matrixRotateZ = new Matrix(4, 4);
    matrixRotateZ->setMatrixItem(0, 0, cos(radians));
    matrixRotateZ->setMatrixItem(0, 1, -sin(radians));
    matrixRotateZ->setMatrixItem(1, 0, sin(radians));
    matrixRotateZ->setMatrixItem(1, 1, cos(radians));
    matrixRotateZ->setMatrixItem(2, 2, 1);
    matrixRotateZ->setMatrixItem(3, 3, 1);

    Obj* obj = (*item).second;
    obj->setGlobalPos((*(obj->getGlobalPos())) * matrixRotateZ);
    matrixRotateZ->~Matrix();
}

//change projection matrix
Matrix* Scene::returnNewProjectionMatrix(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar){
    float aspectRatio = (float)xScreenSize / (float)yScreenSize;
    float fovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * PI);
    float zRange = zNear - zFar;

    // Create a new 4x4 matrix
    Matrix* projMatrix = new Matrix(4, 4);

    // Set matrix items for the projection matrix
    projMatrix->setMatrixItem(0, 0, fovRad / aspectRatio);
    projMatrix->setMatrixItem(0, 1, 0);
    projMatrix->setMatrixItem(0, 2, 0);
    projMatrix->setMatrixItem(0, 3, 0);

    projMatrix->setMatrixItem(1, 0, 0);
    projMatrix->setMatrixItem(1, 1, fovRad);
    projMatrix->setMatrixItem(1, 2, 0);
    projMatrix->setMatrixItem(1, 3, 0);

    projMatrix->setMatrixItem(2, 0, 0);
    projMatrix->setMatrixItem(2, 1, 0);
    projMatrix->setMatrixItem(2, 2, (zFar + zNear) / zRange);
    projMatrix->setMatrixItem(2, 3, (2 * zFar * zNear) / zRange);

    projMatrix->setMatrixItem(3, 0, 0);
    projMatrix->setMatrixItem(3, 1, 0);
    projMatrix->setMatrixItem(3, 2, -1);
    projMatrix->setMatrixItem(3, 3, 0);

    return projMatrix;
}

void Scene::setMyProjectionMatrix(Matrix* newProjMatrix){
    if (this->projMatrix != NULL) this->projMatrix->~Matrix();
    this->projMatrix = newProjMatrix;
}

void Scene::changeSceneVar(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar){
    this->xScreenSize = xScreenSize;
    this->yScreenSize = yScreenSize;
    this->FOV = FOV;
    this->zNear = zNear;
    this->zFar = zFar;
    this->setMyProjectionMatrix(returnNewProjectionMatrix(xScreenSize, yScreenSize, FOV, zNear, zFar));
}

Matrix* Scene::getProjectionMatrix(){ return this->projMatrix; }

//take positions for rendering on screen
std::vector<int*> Scene::returnObjsScreenPos(const char* objName){
    std::vector<int*> allPositions;
    
    //using for any object separately
    std::vector<Matrix*> positionsObj;

    for (std::map<const char*, Obj*>::iterator i = objs.begin(); i != objs.end(); ++i){
        Obj* objItem = (*i).second;
        for (Matrix* itemPos: objItem->getVertex()){
            testPosVertes(itemPos);

            Matrix* newItem = new Matrix(4, 1);
            newItem
        }
    }

}