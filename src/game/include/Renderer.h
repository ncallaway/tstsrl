#ifndef RENDERER_H
#define RENDERER_H

#include "IRenderInfo.h"

class SDL_Renderer;

/**
  A simple implementation of IRenderInfo that takes all of its parameters in the constructor,
  and returns them in the specific functions.
*/
class Renderer : public IRenderInfo {
public:
    /**
      \param [in] sdl_renderer SDL_Renderer* to return via the get_sdl_renderer() function.
    */
    Renderer(SDL_Renderer* sdl_renderer) {
        mp_sdl_renderer = sdl_renderer;
    }

    virtual SDL_Renderer* get_sdl_renderer() { return mp_sdl_renderer; }

private:
    SDL_Renderer* mp_sdl_renderer;
};
#endif // RENDERER_H
