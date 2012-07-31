#include "SDL.h"

int main( int argc, char* args[] )
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );


    window = SDL_CreateWindow("A window", 0, 0, 640, 480, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    // Draw blue 
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL
    SDL_Quit();
    return 0;    
}
