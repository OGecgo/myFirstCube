#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>

void drawScreen(std::vector<int*> draw, int xSize, int ySize){
    //draw
    printf("\x1b[H");
        //screan
        for (int y = 0; y <= ySize; y++){
            for (int x = 0; x <= xSize; x++){
                //positions
                bool b = false; 
                for (int i = 0; i < draw.size(); i++){
                    if(draw[i][0] == x && draw[i][1] == y) b = true;
                }
                if(b) printf(" ");
                else printf("0");
            }
            printf("\n");
        }
            
        usleep(1000 * 1000 * 1);
}

