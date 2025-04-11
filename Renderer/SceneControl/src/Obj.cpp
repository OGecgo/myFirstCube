#include "../Obj.hpp"

#include <stdio.h>

#define Max_Length 128

Obj::Obj(const char* path){
    this->globalPos = new Matrix(4, 1);
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
            Matrix* vertexItem = new Matrix(4, 1);
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            vertexItem->setMatrixItem(0, 0, x);
            vertexItem->setMatrixItem(1, 0, y);
            vertexItem->setMatrixItem(2, 0, z);
            this->vertex.push_back(vertexItem);
        }

        else if (line[0] == 'f' && line[1] == ' '){
            int* facesItem = new int[3];
            int v1, v2, v3, vt1, vt2, vt3, vm1, vm2, vm3;
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &facesItem[0], &vt1, &vm1, &facesItem[1], &vt2, &vm2, &facesItem[2], &vt3, &vm3);
            this->faces.push_back(facesItem);
        }

        else printf("Error line cannot read: %s", line);
    }
}

Obj::~Obj(){
    if (!this->vertex.empty()){
        for(Matrix* item: this->vertex){
            item->~Matrix();
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

std::vector<Matrix*> Obj::getVertex(){ return this->vertex; }
std::vector<int*> Obj::getFaces(){ return this->faces; }  
Matrix* Obj::getGlobalPos(){ return this->globalPos; }
void Obj::setGlobalPos(Matrix* newPos){ this->globalPos = newPos; } 