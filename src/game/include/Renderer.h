#ifndef RENDERER_H
#define RENDERER_H

#include "IRenderInfo.h"

class SDL_Renderer;

class Renderer : public IRenderInfo {
public:
    Renderer(SDL_Renderer* sdl_renderer) {
        mp_sdl_renderer = sdl_renderer;
    }

    virtual SDL_Renderer* get_sdl_renderer() { return mp_sdl_renderer; }

private:
    SDL_Renderer* mp_sdl_renderer;
};
#endif // RENDERER_H
