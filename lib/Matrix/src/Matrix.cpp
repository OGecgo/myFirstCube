#include "../Matrix.hpp"

#include <stdio.h>
#include <cstdlib>

#define rowPos(row) row * this->columnSize
#define testPos(row, column) \
    if ((row) >= this->rowSize || (column) >= this->columnSize ) { \
        printf("Error Matrix: position matrix[row = %d][column = %d] is out of bounds.\n", (row), (column)); \
        exit(1); \
    }


Matrix::Matrix(int rowSize, int columnSize){
    this->rowSize = rowSize;
    this->columnSize = columnSize;
    this->matrix = new float[columnSize * rowSize];
    for (int i = 0; i < (columnSize * rowSize); i++){
        this->matrix[i] = 0.0f;
    }
}
Matrix::~Matrix(){
    if (this->matrix != NULL){
        delete[] this->matrix;
    }
}

void Matrix::printMatrix(){
    printf("\n");
    for (int r = 0; r < this->rowSize; r++){
        printf("[");
        for (int c = 0; c < this->columnSize - 1; c++){
            printf("%f, ", this->getMatrixItem(r, c));
        }
        printf("%f", this->getMatrixItem(r, this->columnSize - 1));
        printf("]\n");
    }
}

int Matrix::getRowSize(){ return this->rowSize; }
int Matrix::getColumnSize(){ return this->columnSize; }

float Matrix::getMatrixItem(int row, int column){
    testPos(row, column);
    float item = this->matrix[rowPos(row) + column];
    return item;
}
void Matrix::setMatrixItem(int column, int row, float item){
    testPos(row, column);
    this->matrix[rowPos(row) + column] = item;
}



Matrix* Matrix::operator*(Matrix* matrix){
    if (this->columnSize != matrix->rowSize){
        printf("Error Matrix: myltiply have leftColumn(%d) != rightRow(%d)\n", this->columnSize, matrix->rowSize);
        exit(1);
    }
    Matrix* newMatrix = new Matrix(this->rowSize, matrix->columnSize);
    for (int thisRow = 0; thisRow < this->rowSize; thisRow++){
        for (int matrixColumn = 0; matrixColumn < matrix->columnSize; matrixColumn++){
            //multiply row with column
            float item = 0.0f;
            for (int thisColumn = 0; thisColumn < this->columnSize; thisColumn++){
                item += this->getMatrixItem(thisRow, thisColumn) * matrix->getMatrixItem(thisColumn, matrixColumn);
            }
            newMatrix->setMatrixItem(matrixColumn, thisRow, item);
        }
    }

    return newMatrix;
}

