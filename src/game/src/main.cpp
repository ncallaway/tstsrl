/**
  \file main.cpp The main entry point for the application. Currently this file
  is responsible for setting up the SDL framework as well as initializing the states.
  
  In the near future, this should ship the work off to a startup manager, which will do all
  necessary application startup work.
*/
#include "SDL.h"
#include "SDL_ttf.h"

#include "StateManager.h"
#include "State.h"
#include "Looper.h"

#include "States.h"
#include "MainMenuState.h"
#include "ControllerSelectState.h"
#include "GameState.h"
#include "Renderer.h"

/**
  main() function of the application.

  \param argc the count of arguments in the args array.
  \param args the array of command line arguments.
  \return the exit code. 0 on success, nonzero on failure.
*/
int main( int argc, char* args[] )
{
    SDL_Window* p_window;
    SDL_Renderer* p_renderer;
    StateManager* p_state_manager;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();

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
