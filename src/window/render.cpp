#include "./header/render.hpp"

render::render(int xSizeScreen, int ySizeScreen, int sizeRenderer, Uint8 red, Uint8 green, Uint8 blue){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("ERROR: SDL not initialize, %s\n", SDL_GetError());
    else{;
        //create window
        SDL_CreateWindowAndRenderer(xSizeScreen * sizeRenderer, ySizeScreen * sizeRenderer, 0, &window, &renderer);

        if (window == NULL || renderer == NULL) printf("ERROR: Window not created, %s\n", SDL_GetError());  
        else{
            SDL_RenderSetScale(renderer, sizeRenderer, sizeRenderer);
            SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
            SDL_RenderClear(renderer);
        }
    };
}

void render::makeFrame(std::vector<int*> pos){// hwris hroma akoma
    //white positions
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int* item: pos){
        SDL_RenderDrawPoint(renderer, item[0], item[1]);
    }
    SDL_RenderPresent(renderer);
};

render::~render(){
    //destroy window
    SDL_DestroyWindow(window);
    SDL_Quit();
}



    