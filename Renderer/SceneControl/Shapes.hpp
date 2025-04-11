#ifndef SHAPES_H
#define SHAPES_H

#include "../../lib/Matrix/Matrix.hpp"
#include <vector>

//return vector with array [x, y]

//return all positions between the positions
std::vector<int*> returnLinePos(Matrix* pos1, Matrix* pos2);
std::vector<int*> returnTrianglePos(Matrix* pos1, Matrix* pos2, Matrix* pos3);
//array of matrix*
std::vector<int*> returnPolygoPos(Matrix* positions);

#endif // SHAPES_H