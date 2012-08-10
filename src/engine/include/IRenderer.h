#ifndef I_RENDERER_H
#define I_RENDERER_H

class SDL_Renderer;

class IRenderer {
public:
    virtual ~IRenderer() {};
    
    virtual SDL_Renderer* get_sdl_renderer() = 0;
};
#endif // I_RENDERER_H
