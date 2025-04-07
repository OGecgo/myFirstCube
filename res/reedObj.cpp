#include "./header/reedObj.hpp"

#include <stdio.h>

#define Max_Length 128

reedObj::reedObj(const char* path){

    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("Error: Failed open file %s\n", path);
        return;
    }

    char line[Max_Length];
    int pos = -1; // because start with space

    while(fgets(line, sizeof(line), file)){
        float num = 0;
        int neg = 1;
        if (line[0] == '#' || line[0] == '\n') continue;

        else if (line[0] == 'v' && line[1] == ' '){
            float* vertexItem = new float[3];
            sscanf(line,"v %f %f %f", &vertexItem[0], &vertexItem[1], &vertexItem[2]);
            this->vertex.push_back(vertexItem);
        }

        else if (line[0] == 'f' && line[1] == ' '){
            int* facesItem = new int[3];
            int vt1, vt2, vt3, vm1, vm2, vm3;
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &facesItem[0], &vt1, &vm1, &facesItem[1], &vt2, &vm2, &facesItem[2], &vt3, &vm3);
            this->faces.push_back(facesItem);
        }

        else printf("Error line cannot read: %s", line);
    }
}

reedObj::~reedObj(){
    if (!this->vertex.empty()){
        for(float* item: this->vertex){
            delete[] item;
        }
        this->vertex.clear();
    }
    if (!this->faces.empty()){
        for(int* item: this->faces){
            delete[] item;
        }
        this->vertex.clear(); 
    }
}

std::vector<float*> reedObj::getVertex(){ return this->vertex; }
std::vector<int*> reedObj::getFaces(){ return this->faces; }