#include "SDL.h"

#include "Looper.h"
int render_draw_color = 0;
SDL_Renderer* renderer = NULL;

bool update(double t, double dt) {
    render_draw_color += 10;
    if (render_draw_color > 255) {
        render_draw_color = 0;
    }
    if (t > 5) {
        return true;
    }
    return false;
}

bool render(double alpha) {
    SDL_SetRenderDrawColor(renderer, render_draw_color, render_draw_color, render_draw_color, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return false;
}

int main( int argc, char* args[] )
{
    SDL_Window* window;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    window = SDL_CreateWindow("A window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    LooperConfiguration configuration;
    configuration.capture_function = NULL;
    configuration.update_function = &update;
    configuration.render_function = &render;
    configuration.update_dt = .1;
    configuration.max_frame_time = .25;

    Looper* looper = new Looper();
    looper->set_configuration(configuration);
    looper->loop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL
    SDL_Quit();
    return 0;    
}
