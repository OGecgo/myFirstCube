#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <vector>

class render{
    private:
        SDL_Window* window;
        SDL_Surface* screenSurFace;
    public:
        render(int xSizeScreen, int ySizeScreen, Uint8 red, Uint8 green, Uint8 blue);
        void render::makeFrame(std::vector<int*> pos);
        ~render();
};


#endif // RENDER_H