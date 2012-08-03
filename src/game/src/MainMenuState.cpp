#include "MainMenuState.h"

MainMenuState::MainMenuState(SDL_Renderer* pRenderer) {
    m_pRenderer = pRenderer;
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

    return t > 10;
}

bool MainMenuState::render(double alpha) {
    int c = (int)((double)m_color_value*alpha + (double)m_previous_color_value*(1.0-alpha));

    SDL_SetRenderDrawColor(m_pRenderer, c, c, c, 255);
    SDL_RenderClear(m_pRenderer);
    SDL_RenderPresent(m_pRenderer);
    return false;
}
