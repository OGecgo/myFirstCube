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
        myConverts(int xSizeScreen, int ySizeScreen, float FOV, float zNear, float zFar);
        ~myConverts();

        // float = int / 100.000,0
        std::vector<float*> returnNormalizedUnitRange(std::vector<int*> pos);

        std::vector<float*> returnNormalizedPos(std::vector<float*> pos);

        // first normilizePosition
        std::vector<int*> returnPosScreen(std::vector<float*> pos);

};
#endif // MYCONVERTS_H