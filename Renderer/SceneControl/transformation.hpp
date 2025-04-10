#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

float* returnMove(float* matrixPos, float x, float y, float z);
float* returnRotateX(float* matrixPos, float angle);
float* returnRotateY(float* matrixPos, float angle);
float* returnRotateZ(float* matrixPos, float angle);

#endif // TRANSFORMATION_H