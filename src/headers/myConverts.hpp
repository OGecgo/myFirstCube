#ifndef MYCONVERTS_H
#define MYCONVERTS_H 

#include <vector>
//converts only for 3d dimentions, that mean vectors have item array with size 4 (x, y, z, w)

// float = int / 100.000,0
std::vector<float*> returnNormalizedUnitRange(std::vector<int*> pos);

void normalizePos(std::vector<float*> pos);

std::vector<int*> returnPosScrean(std::vector<float*> pos);

#endif // MYCONVERTS_H