#include "./header/render.hpp"

render::render(int xSizeScreen, int ySizeScreen, int sizeRenderer, Uint8 red, Uint8 green, Uint8 blue){
    this->red = red;
    this->green = green;
    this->blue = blue;

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

render::~render() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void render::makeFrame(std::vector<int*> pos){// hwris hroma akoma
    //white positions
    SDL_SetRenderDrawColor(renderer, this->red, this->green, this->blue, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int* item: pos){
        SDL_RenderDrawPoint(renderer, item[0], item[1]);
    }
    SDL_RenderPresent(renderer);
};

void render::delay(int ms){
    SDL_Delay(ms);
}



    