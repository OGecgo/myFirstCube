#include "./headers/readTxt.hpp"

#include <stdio.h>
#include <cstdlib>


std::vector<int*> returnVectorIntArrayFromTxt(const char* path, int sizeInt){
    std::vector<int*> vec;
    FILE* file = fopen(path, "r");

    if (file == NULL){
        printf("Failed to open %s", path);
        return vec;
    }

    char ch;
    int*  array;
    int pos = 0;
    if (fgetc(file) == '<'){// start vec
        while ((ch = fgetc(file)) != EOF){
            if (ch == '>') break; // end vec

            if (ch == '['){ // start array
                array = (int*)malloc(sizeof(int) * sizeInt);
                while ((ch = fgetc(file)) != EOF){  
                    if (ch == ']')  { // end the array and add it to vec
                        vec.push_back(array);
                        break;
                    }
                    if (ch >= 48 && ch <= 57){ // 123 + 1 => 1231 and add number
                            int n = (int)ch - 48;
                            array[pos] = (array[pos] * 10) + n;
                        }
                    if (ch == ',') pos++; // next number
                }
                pos = 0;
            }
        }
    }
    fclose(file);

    return vec;

}