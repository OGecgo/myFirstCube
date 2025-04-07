#ifndef REEDOBJ_H
#define REEDOBJ_H

#include <vector>

class reedObj{
    private:
        std::vector<float*> vertex;
        std::vector<int*> faces;
    public:
        reedObj(const char* path);
        ~reedObj();
        std::vector<float*> getVertex();
        std::vector<int*> getFaces();
};


#endif // REEDOBJ_H