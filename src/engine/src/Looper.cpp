#include "Looper.h"

void Looper::loop(SDL_Renderer* pRenderer) {
    while (SDL_GetTicks() < 20000) {
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);
    }
}
