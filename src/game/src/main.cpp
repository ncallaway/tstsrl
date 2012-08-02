#include "SDL.h"

#include "Looper.h"

int main( int argc, char* args[] )
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    window = SDL_CreateWindow("A window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    // Draw green 
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    Looper* looper = new Looper();
    looper->loop(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL
    SDL_Quit();
    return 0;    
}
