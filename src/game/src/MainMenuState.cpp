#include "MainMenuState.h"

#include "IRenderInfo.h"
#include "IStateChanger.h"

#include "States.h"

MainMenuState::MainMenuState(IStateChanger* state_changer, IRenderInfo* renderer) {
    mp_state_changer = state_changer;
    mp_renderer = renderer;
}

void MainMenuState::start() {
    m_going_up = true;
    m_previous_color_value = 0;
    m_color_value = 0;
}

bool MainMenuState::event(SDL_Event* event) {
    switch(event->type) {
    case SDL_QUIT:
        return true;
    case SDL_KEYUP:
        if (event->key.keysym.sym == SDLK_RIGHT) {
            mp_state_changer->set_next_state(CONTROLLER_SELECT_STATE);
        }
        return false;
    default:
        return false; 
    }
}

bool MainMenuState::capture() {
    m_previous_color_value = m_color_value;
    return false;
}

bool MainMenuState::update(double t, double dt) {
    m_color_value += m_going_up ? 10 : -10;

    if (m_color_value > 255) {
        m_color_value = 255;
        m_going_up = false;
    } else if (m_color_value < 0) {
        m_color_value = 0;
        m_going_up = true;
    }

    return false;
}

bool MainMenuState::render(double alpha) {

    int c = (int)((double)m_color_value*alpha + (double)m_previous_color_value*(1.0-alpha));

    SDL_Renderer* p_sdl_renderer = mp_renderer->get_sdl_renderer();

    SDL_SetRenderDrawColor(p_sdl_renderer, c, c, c, 255);
    SDL_RenderClear(p_sdl_renderer);
    SDL_RenderPresent(p_sdl_renderer);
    return false;
}
