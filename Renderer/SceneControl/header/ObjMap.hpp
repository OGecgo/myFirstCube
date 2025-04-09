#ifndef OBJMAP_H
#define OBJMAP_H

#include "./../../res/header/ReadObj.hpp"

#include <vector>
#include <map>

class ObjMap{

    private:
        std::map<const char*, ReadObj> objs; // name -> objects
        float* projMatrix; 
        int xScreenSize, yScreenSize; // parameters camera
        float FOV, zNear, zFar;

    public:
        //initialize map with projection matrix
        ObjMap(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar);
        ~ObjMap();

        //add obj to map
        void openObj(const char* path);

        //transformations
        void moveObj(const char* objName, float x, float y, float z);
        void rotateXObj(const char* objName, int angle);
        void rotateYObj(const char* objName, int angle);
        void rotateZObj(const char* objName, int angle);

        //change projecton matrix
        void setMyProjectionMatrix(float* newProjMatrix);
        void changeProjectionMatrixVar(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar);
        
        //take positions for drawiing
        std::vector<int*> returnObjScreenPos(const char* objName);


};

#endif // OBJMAP_H