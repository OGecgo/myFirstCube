#ifndef MATRIX_H
#define MATRIX_H


class Matrix{
    private:
        float* matrix;
        int rowSize, columnSize;
    public:
        //matrix initialized with 0
        Matrix(int rowSize, int columnSize);
        ~Matrix();
        void printMatrix();
        int getRowSize();
        int getColumnSize();
        float getMatrixItem(int row, int column);
        void setMatrixItem(int row, int column, float item);
        Matrix* operator*(Matrix* matrix);
        Matrix* operator*=(Matrix* matrix);
};

#endif // MATRIX_H 