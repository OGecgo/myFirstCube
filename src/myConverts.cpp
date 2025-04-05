#include "./headers/myConverts.hpp"

#include <cstdlib>

std::vector<float*> returnNormalizedUnitRange(std::vector<int*> pos){
    std::vector<float*> newPos;
    for (int* item: pos){
        float* arrayOfFloats = (float*)malloc(sizeof(float) * 4);
        for(int i = 0; i < 4; i++){
            arrayOfFloats[i] = item[i] / 100000.0;
        }
        newPos.push_back(arrayOfFloats);
    }
    
    return newPos;
}

void normalizePos(std::vector<float*> pos){}

std::vector<int*> returnPosScrean(std::vector<float*> pos){

    std::vector<int*> vec;
    return vec;
}