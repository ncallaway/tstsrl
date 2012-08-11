#include "MainMenuState.h"

#include "IRenderInfo.h"
#include "IStateChanger.h"

#include "States.h"

MainMenuState::MainMenuState(IStateChanger* state_changer, IRenderInfo* renderer) {
    mp_state_changer = state_changer;
    mp_renderer = renderer;

    mp_selected_font = NULL;
    mp_title = NULL; 
}

void MainMenuState::start() {
    if (mp_selected_font == NULL) {
        mp_selected_font = TTF_OpenFont("assets/fonts/quicksand_book.ttf", 24);
    }

    SDL_Color font_color = {155, 155, 255};
    SDL_Color bg_color = {255, 255, 255};

    TTF_SetFontHinting(mp_selected_font, TTF_HINTING_LIGHT);
    SDL_Surface* tmp_surface = TTF_RenderUTF8_Shaded(mp_selected_font, "Twin-Stick Tactical-Shooter Rogue-Like", font_color, bg_color);
    SDL_Renderer* renderer = mp_renderer->get_sdl_renderer();
    mp_title = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
}

void MainMenuState::stop() {
    SDL_DestroyTexture(mp_title);
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
    return false;
}

bool MainMenuState::update(double t, double dt) {
    return false;
}

bool MainMenuState::render(double alpha) {

    SDL_Renderer* p_sdl_renderer = mp_renderer->get_sdl_renderer();

    SDL_SetRenderDrawColor(p_sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(p_sdl_renderer);

    Uint32 format;
    int access, w, h;

    SDL_QueryTexture(mp_title, &format, &access, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_Rect dst = {100, 10, w, h};

    SDL_RenderCopy(p_sdl_renderer, mp_title, &src, &dst);
    
    SDL_RenderPresent(p_sdl_renderer);
    return false;
}
