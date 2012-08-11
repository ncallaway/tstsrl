#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "SDL.h"
#include "SDL_ttf.h"

#include "State.h" // Required for subclass of State

class IStateChanger;
class IRenderInfo;

/**
  The state responsible for displaying the main menu.
*/
class MainMenuState : public State {
public:
    /**
      \param [in] state_changer The IStateChanger that can change between various states.
      \param [in] renderer The IRenderInfo that contains the data necessary to render the menu.
    */
    MainMenuState(IStateChanger* state_changer, IRenderInfo* renderer);

    virtual void start();
    virtual void stop();
    
    virtual bool event(SDL_Event* event);
    virtual bool capture();
    virtual bool update(double t, double dt);
    virtual bool render(double alpha);

private:
    IRenderInfo* mp_renderer; 
    IStateChanger* mp_state_changer;

    TTF_Font* mp_selected_font;
    SDL_Texture* mp_title;
};

#endif // MAIN_MENU_STATE_H
