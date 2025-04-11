#include "./Shapes.hpp"

#include <cmath>




//return all positions between the posittions
std::vector<int*> returnLinePos(Matrix* pos1, Matrix* pos2){
    //used BresenhamLine Algorithm
    std::vector<int*> positions;

    //positions
    int x1 = pos1->getMatrixItem(0, 0), y1 = pos1->getMatrixItem(1, 0);
    int x2 = pos2->getMatrixItem(0, 0), y2 = pos2->getMatrixItem(1, 0);

    //distance 
    int dx = abs(x2 - x1), dy = abs(y2 - y1);

    //direction
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    //err and e2 to understan if i need to move pixel or not
    int err = dx - dy;

    //add item
    int* posN = new int[2];
    posN[0] = x1; posN[1] = y1;
    positions.push_back(posN);

    // suc x1 and y1 until they equal ot startPositions
    while (x1 != x2 || y1 != y2){

        // addition when e2 is cose to 0
        int e2 = 2 * err;

        // a * dy < dx when a is odd
        // if line more close to next pixely
        if (e2 > -dy) {
            //move err to next pixel y
            err -= dy;
            x1 += sx;
        }

        //a * dx < dy when a in odd.s
        //if line more close to bext pixel x
        if (e2 < dx) {
            //move err to next pixel x
            err += dx;
            y1 += sy;
        }

        //add item
        int* posN = new int[2];
        posN[0] = x1; posN[1] = y1;
        positions.push_back(posN);
    }

    return positions;
}
std::vector<int*> returnTrianglePos(Matrix* pos1, Matrix* pos2, Matrix* pos3){
    //set positions
    std::vector<int*> positions1 = returnLinePos(pos1, pos2);
    std::vector<int*> positions2 = returnLinePos(pos2, pos3);
    std::vector<int*> positions3 = returnLinePos(pos3, pos1);
    std::vector<int*> newPos;
    newPos.insert(positions1.end(), positions2.begin(), positions2.end());
    newPos.insert(newPos.end(), positions3.begin(), positions3.end());

    // Free memory
    for (int* pos : positions1) delete[] pos;
    for (int* pos : positions2) delete[] pos;
    for (int* pos : positions3) delete[] pos;
    positions1.~vector();
    positions2.~vector();
    positions3.~vector();

    return newPos;
}


//array of matrix*
std::vector<int*> returnPolygoPos(Matrix* positions){
    std::vector<int*> null;
    return null;
}