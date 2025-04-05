#include "./headers/readTxt.hpp"

#include <stdio.h>
#include <cstdlib>


std::vector<int*> returnVectorIntArrayFromTxt(const char* path, int sizeInt){
    std::vector<int*> vec;
    FILE* file = fopen(path, "r");

    if (file == NULL){// test
        printf("Error: Failed to open %s", path);
        return vec;
    }

    char ch;
    int boolArray = 0; // new item
    int* array; // item for vector
    int pos; //position of array
    int neg = 1; //for negativ number
    if (fgetc(file) == '<'){// start vec
        while ((ch = fgetc(file)) != EOF){

            if (ch == '['){ 
                boolArray = 1;
                array = (int*)malloc(sizeof(int) * sizeInt);
                pos = 0;
                array[pos] = 0;
            }
            if (boolArray){ // start array
                if (ch == ']')  { // end the array and add it to vec
                    vec.push_back(array);
                    boolArray = 0;
                    pos = 0;
                    continue;
                }    
                if (ch == '-') neg = -1;
                if (ch >= '0' && ch <= '9'){ // 123 + 1 => 1231 and add number
                    array[pos] = (array[pos] * 10) + (ch - '0');
                }
                if (ch == ',') { // next number
                     array[pos] *= neg;
                    pos++;
                    array[pos] = 0;
                    neg = 1;
                }  

    
            }

            if (ch == '>') break; // end vec
        }
    }
    fclose(file);

    return vec;

}