#include "./res/headers/readTxt.hpp"

#include <stdio.h>
#include <vector>

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

int main(){

    //run file is on root Cube
    const char* path = "./res/txtFiles/vectorPos.txt";
    std::vector<int*> vectorPos = returnVectorIntArrayFromTxt(path, 4); // no 1 to -1 but 1000 to -1000 and then make 1000 => 1
    printVector(vectorPos, 4);

}