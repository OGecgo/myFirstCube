#ifndef MYCONVERTS_H
#define MYCONVERTS_H 

#include <vector>
//converts only for 3d dimentions, that mean vectors have item array with size 4 (x, y, z, w)

class myConverts{
    private: 
        float* projMatrix;
        int xSizeScreen;
        int ySizeScreen;
        float FOV;
        float zNear;
        float zFar;

    public:
        //constractor-deconstractor
        myConverts();
        //make with projection matrix
        myConverts(int xSizeScreen, int ySizeScreen, float FOV, float zNear, float zFar);
        ~myConverts();

        //getters-setter for every item
        int getXSizeScreen();
        int getYSizeScreen();
        float getFOV();
        float getZNear();
        float getZFar();
        float* getProjMatrix();
        
        //if change something projectio Matrix dont changed !
        void setXSizeScreen(int xSizeScreen);
        void setYSizeScreen(int ySizeScreen);
        void setFOV(float FOV);
        void setZNear(float zNear);
        void setZFar(float zFar);
        void setProjMatrix(float* projMatrix);


        // float = int / 100.000,0
        std::vector<float*> returnNormalizedUnitRange(std::vector<int*> pos);

        std::vector<float*> returnNormalizedPos(std::vector<float*> pos);

        // first normilizePosition
        std::vector<int*> returnPosScreen(std::vector<float*> pos);

};
#endif // MYCONVERTS_H