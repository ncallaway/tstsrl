#include "SDL.h"

#include "State.h"
#include "Looper.h"

#include "MainMenuState.h"

State* pState;

bool event(SDL_Event* event) {
    return pState->event(event);
}

bool capture() {
    return pState->capture();
}

bool update(double t, double dt) {
    return pState->update(t, dt);
}

bool render(double alpha) {
    return pState->render(alpha);
}

int main( int argc, char* args[] )
{
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    pWindow = SDL_CreateWindow("A window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

    pState = new MainMenuState(pRenderer);
    pState->start();

    LooperConfiguration configuration;
    configuration.event_function = &event;
    configuration.capture_function = &capture;
    configuration.update_function = &update;
    configuration.render_function = &render;
    configuration.update_dt = .1;
    configuration.max_frame_time = .25;

    Looper* looper = new Looper();
    looper->set_configuration(configuration);
    looper->loop();

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    
    // Quit SDL
    SDL_Quit();
    return 0;    
}
