#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <vector>

class render{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        render(int xSizeScreen, int ySizeScreen, int sizeRenderer, Uint8 red, Uint8 green, Uint8 blue);
        void makeFrame(std::vector<int*> pos);
        ~render();
};


#endif // RENDER_H