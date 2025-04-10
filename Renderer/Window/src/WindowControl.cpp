#include "../WindowControl.hpp"
int fsda(){}

//polu hazi ilopoiisi
int windowClosed(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT) return 1;
    }
    return 0;
}
