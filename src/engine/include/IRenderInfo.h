#ifndef I_RENDERER_H
#define I_RENDERER_H

class SDL_Renderer;

/**
  Interface that describes how to get the necessary componets for performing
  rendering tasks.
*/
class IRenderInfo {
public:
    virtual ~IRenderInfo() {};

    /**
      Get the SDL_Renderer that this render info contains.

      \return The SDL_Renderer to use to render things to the screen.
    */
    virtual SDL_Renderer* get_sdl_renderer() = 0;
};
#endif // I_RENDERER_H
