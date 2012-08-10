#include "ControllerSelectState.h"

#include "IRenderer.h"
#include "IStateChanger.h"

#include "States.h"

ControllerSelectState::ControllerSelectState(IStateChanger* state_changer, IRenderer* renderer) {
    mp_state_changer = state_changer;
    mp_renderer = renderer;
}

void ControllerSelectState::start() {
    m_going_up = true;
    m_previous_color_value = 0;
    m_color_value = 0;
}

bool ControllerSelectState::event(SDL_Event* event) {
    switch(event->type) {
    case SDL_QUIT:
        return true;
    case SDL_KEYUP:
        if (event->key.keysym.sym == SDLK_LEFT) {
            mp_state_changer->set_next_state(MAIN_MENU_STATE);
        } else if (event->key.keysym.sym == SDLK_RIGHT) {
            mp_state_changer->set_next_state(GAME_STATE);
        }
    default:
        return false; 
    }
}

bool ControllerSelectState::capture() {
    m_previous_color_value = m_color_value;
    return false;
}

bool ControllerSelectState::update(double t, double dt) {
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

bool ControllerSelectState::render(double alpha) {

    int c = (int)((double)m_color_value*alpha + (double)m_previous_color_value*(1.0-alpha));

    SDL_Renderer* p_sdl_renderer = mp_renderer->get_sdl_renderer();

    SDL_SetRenderDrawColor(p_sdl_renderer, c, 0, 0, 255);
    SDL_RenderClear(p_sdl_renderer);
    SDL_RenderPresent(p_sdl_renderer);
    return false;
}
