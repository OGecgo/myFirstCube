#include "./header/render.hpp"

render::render(int xSizeScreen, int ySizeScreen, Uint8 red, Uint8 green, Uint8 blue){

    if ( SDL_Init( SDL_INIT_VIDEO) < 0) printf("ERROR: SDL not initialize, %s\n", SDL_GetError());
    else{
        //create window
        window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, xSizeScreen, ySizeScreen, SDL_WINDOW_SHOWN);
        if (window == NULL) printf("ERROR: Window not created, %s\n", SDL_GetError());  
        else{
            //Get wundow surface
            screenSurFace = SDL_GetWindowSurface(window);
            //Fill with color the survace
            SDL_FillRect(screenSurFace, NULL, SDL_MapRGB(screenSurFace->format, red, green, blue));
            SDL_UpdateWindowSurface(window);
        }
    }
}

void render::makeFrame(std::vector<int*> pos){
    SDL_FillRect(screenSurFace, NULL, SDL_MapRGB(screenSurFace->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
}

render::~render(){
    //destroy window
    SDL_DestroyWindow(window);
    //Quit SDL sybsystems
    SDL_Quit();
}



    