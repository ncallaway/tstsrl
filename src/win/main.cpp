#include "SDL.h"

int main( int argc, char* args[] )
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

	SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, 0);

	while (SDL_GetTicks() < 3000);
    
    //Quit SDL
    SDL_Quit();
    
    return 0;    
}