#include "./Matrix.hpp"

#include <stdio.h>

int main(){

    //test initialize
    Matrix* myMatrix1 = new Matrix(4, 4);
    myMatrix1->setMatrixItem(0, 0, 1);
    myMatrix1->setMatrixItem(1, 1, 1);
    myMatrix1->setMatrixItem(2, 2, 1);

    myMatrix1->setMatrixItem(3, 0, 1);
    myMatrix1->setMatrixItem(3, 1, 1);
    myMatrix1->setMatrixItem(3, 2, 1);
    myMatrix1->setMatrixItem(3, 3, 1);

    Matrix* myMatrix2 = new Matrix(4, 1);
    myMatrix2->setMatrixItem(0, 0, 1);
    myMatrix2->setMatrixItem(0, 1, 2);
    myMatrix2->setMatrixItem(0, 2, 3);
    myMatrix2->setMatrixItem(0, 3, 1);
    
    //test print
    myMatrix1->printMatrix();
    myMatrix2->printMatrix();
    printf("myMatrix1Size = rows(%d), columns(%d)\n", myMatrix1->getRowSize(), myMatrix1->getColumnSize());
    printf("myMatrix2Size = rows(%d), columns(%d)\n", myMatrix2->getRowSize(), myMatrix2->getColumnSize());

    //test multiply
    Matrix* newMatrix = (* myMatrix1) * (myMatrix2);
    newMatrix->printMatrix();
    printf("newMatrixSize = rows(%d), columns(%d)\n", newMatrix->getRowSize(), newMatrix->getRowSize());

    return 0;
}