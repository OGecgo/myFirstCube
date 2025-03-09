#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <vector>

float* callProjMatrix(int xSize, int ySize, int FOV, int zNear, int zFar);
float* callTransformations(float X, float Y, float Z);
float* callRotateX(float angel);
float* callRotateY(float angel);
float* callRotateZ(float angel);
void BresenhamLineAlgorithm(std::vector<int*>& vec, int* pos1, int* pos2);
void addMatrix(std::vector<float*>& face, float* Matrix);
void multiplyMatrix(std::vector<float*>& face, float* Matrix);
std::vector<int*> convertPositions(std::vector<float*> face, int xSize, int ySize);

#endif // MYVECTOR_H