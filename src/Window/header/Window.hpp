#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <vector>

class Window{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Uint8 red, green, blue;
    public:
        Window(int xSizeScreen, int ySizeScreen, int sizeRenderer, Uint8 red, Uint8 green, Uint8 blue);
        ~Window();
        void makeFrame(std::vector<int*> pos);
        void delay(int ms);
};


#endif // WINDOW_H