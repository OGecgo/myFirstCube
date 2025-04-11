#ifndef SCENE_H
#define SCENE_H

#include "./Obj.hpp"

#include "../../lib/Matrix/Matrix.hpp"
#include <vector>
#include <map>

class Scene{

    private:
        std::map<const char*, Obj*> objs; // name -> objects
        Matrix* projMatrix; 

        int xScreenSize, yScreenSize; // parameters camera
        float FOV, zNear, zFar;

    public:
        //initialize map with projection matrix
        Scene(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar);
        ~Scene();

        //add obj to map
        void openObj(const char* path);

        //transformations
        void moveObj(const char* objName, float x, float y, float z);
        void rotateXObj(const char* objName, int angle);
        void rotateYObj(const char* objName, int angle);
        void rotateZObj(const char* objName, int angle);

        //change projection matrix
        Matrix* returnNewProjectionMatrix(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar);
        void setMyProjectionMatrix(Matrix* newProjMatrix);
        void changeSceneVar(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar);
	    Matrix* getProjectionMatrix();
	
        //take positions for rendering on screen
        std::vector<int*> returnObjsScreenPos(const char* objName);


};

#endif // SCENE_H
