#ifndef READOBJ_H
#define READOBJ_H

#include <vector>

class ReadObj{
    private:
        std::vector<float*> vertex;
        std::vector<int*> faces;
        float globalPos;
    public:
        ReadObj(const char* path);
        ~ReadObj();
        std::vector<float*> getVertex();
        std::vector<int*> getFaces();
        float getGlobalPos();
        void setGlobalPos(float newPos); 

};


#endif // READOBJ_H
