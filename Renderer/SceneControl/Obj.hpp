#ifndef OBJ_H
#define OBJ_H

#include "../../lib/Matrix/Matrix.hpp"
#include <vector>

class Obj{
    private:
        std::vector<Matrix*> vertex;
        std::vector<int*> faces;
        Matrix* globalPos;
    public:
        Obj(const char* path);
        ~Obj();

        std::vector<Matrix*> getVertex();
        std::vector<int*> getFaces();

        Matrix* getGlobalPos();
        std::vector<Matrix*> returnCovertedVertexToGlobalVertex();
        void setGlobalPos(float x, float y, float z);
        void setGlobalPos(Matrix* pos);

};


#endif // OBJ_H
