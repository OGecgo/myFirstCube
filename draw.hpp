#ifndef DRAW_HPP
#define DRAW_HPP

#include <vector>

void makeTringle(std::vector<int*>& vec, int* pos1, int* pos2, int* pos3);
void drawFace(std::vector<int*>& vec, int* pos1, int* pos2, int* pos3, int* pos4);
void drawScreen(std::vector<int*> draw, int xSize, int ySize);
void drawCube(std::vector<int*>& vec);
#endif // DRAW_HPP