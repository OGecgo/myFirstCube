#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <vector>

void printVector(std::vector<float*> vec);
float* callProjMatrix(int xSize, int ySize, float FOV, float zNear, float zFar);    float* callTransformations(float X, float Y, float Z);
float* callRotateX(float angel);
float* callRotateY(float angel);
float* callRotateZ(float angel);
void BresenhamLineAlgorithm(std::vector<int*>& vec, int* pos1, int* pos2);
void addMatrix(std::vector<float*>& face, float* Matrix);
float* returnMultiplyMatrixPos4x1_4x4(float* Matrix, std::vector<float*>& Pos);
void multiplyMatrixPos4x1_4x4(float* Matrix, std::vector<float*>& Pos);
void multiplyMatrix4x4(float* &matrix1, float* matrix2);
std::vector<int*> convertPositions(std::vector<float*> face, int xSize, int ySize);
std::vector<int*> convertPositions(float* Pos, int size, int xSize, int ySize);

#endif // MYMATRIX_H