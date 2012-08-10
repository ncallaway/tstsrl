#include "SDL.h"

#include "StateManager.h"
#include "State.h"
#include "Looper.h"

#include "States.h"
#include "MainMenuState.h"
#include "ControllerSelectState.h"
#include "GameState.h"
#include "Renderer.h"

int main( int argc, char* args[] )
{
    SDL_Window* p_window;
    SDL_Renderer* p_renderer;
    StateManager* p_state_manager;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    p_window = SDL_CreateWindow("A window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    p_renderer = SDL_CreateRenderer(p_window, -1, 0);

    Renderer* renderer = new Renderer(p_renderer);

    p_state_manager = new StateManager();
    p_state_manager->register_state(MAIN_MENU_STATE, new MainMenuState(p_state_manager, renderer));
    p_state_manager->register_state(CONTROLLER_SELECT_STATE, new ControllerSelectState(p_state_manager, renderer)); 
    p_state_manager->register_state(GAME_STATE, new GameState(p_state_manager, renderer)); 
    p_state_manager->set_next_state(MAIN_MENU_STATE);

    LooperConfiguration configuration;
    configuration.loop_moderator = p_state_manager;
    configuration.update_dt = .1;
    configuration.max_frame_time = .25;

    Looper* looper = new Looper();
    looper->set_configuration(configuration);
    looper->loop();

    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyWindow(p_window);
    
    // Quit SDL
    SDL_Quit();
    return 0;    
}
