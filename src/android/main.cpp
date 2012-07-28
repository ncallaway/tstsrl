#include "SDL.h"

int main( int argc, char* args[] )
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("A window", 0, 0, 640, 480, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

    //while (SDL_GetTicks() < 3000);
	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    //Quit SDL
    SDL_Quit();
    return 0;    
}
