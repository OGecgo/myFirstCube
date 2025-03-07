#include <stdio.h>

#include <vector>
#include <cmath>

//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#:~:text=Bresenham's%20line%20algorithm%20is%20a,straight%20line%20between%20two%20points.
void setVectorLine(std::vector<int*>* vec, int* pos1, int* pos2) {
    // positions
    int x1 = pos1[0], y1 = pos1[1];
    int x2 = pos2[0], y2 = pos2[1];
    
    //distance
    int dx = abs(x2 - x1), dy = abs(y2 - y1);

    //direction 
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    //err and e2 to understan if i need to move pixel or not
    int err = dx - dy;

    //add value
    int* posN = (int*)malloc(sizeof(int) * 2);
    posN[0] = x1;
    posN[1] = y1;
    vec->push_back(posN);
    //printf("Added position: (%d, %d)\n", x1, y1); // Debug print

    // sub x1 and y1 until they equal to startPositions
    while (x1 != x2 || y1 != y2) {

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
        //add value
        int* posN = (int*)malloc(sizeof(int) * 2);
        posN[0] = x1;
        posN[1] = y1;
        vec->push_back(posN);
        //printf("Added position: (%d, %d)\n", x1, y1); // Debug print
    }
}

std::vector<int*> normilizePositions(std::vector<float*> face, int sizeX, int sizeY) {
    float projection[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},  
        {0, 0, 0, 1}
    };

    std::vector<int*> result;

    for (int i = 0; i < face.size(); i++) {
        float x = face[i][0] * projection[0][0] + face[i][1] * projection[1][0] + face[i][2] * projection[2][0] + face[i][3] * projection[3][0];
        float y = face[i][0] * projection[0][1] + face[i][1] * projection[1][1] + face[i][2] * projection[2][1] + face[i][3] * projection[3][1];
        float z = face[i][0] * projection[0][2] + face[i][1] * projection[1][2] + face[i][2] * projection[2][2] + face[i][3] * projection[3][2];
        float w = face[i][0] * projection[0][3] + face[i][1] * projection[1][3] + face[i][2] * projection[2][3] + face[i][3] * projection[3][3];

        // normilize
        if (w != 0) {
            x /= w;
            y /= w;
        }

        // covert to screan position when midle position is 0
        int screenX = (int)((x + 1) * (sizeX / 2.0));
        int screenY = (int)((y + 1) * (sizeY / 2.0));

        // set value
        int* newPos = (int*)malloc(sizeof(int) * 2);
        newPos[0] = screenX;
        newPos[1] = screenY;
        result.push_back(newPos);

        // Debug print
        //printf("3D Position: (%f, %f, %f, %f) -> 2D Position: (%d, %d)\n", face[i][0], face[i][1], face[i][2], face[i][3], screenX, screenY);
    }
    return result;
}
