#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "SDL.h"

#include "State.h" // Required for subclass of State

class IStateChanger;
class IRenderInfo;

class MainMenuState : public State {
public:
    MainMenuState(IStateChanger* state_changer, IRenderInfo* renderer);

    virtual void start();
    
    virtual bool event(SDL_Event* event);
    virtual bool capture();
    virtual bool update(double t, double dt);
    virtual bool render(double alpha);

private:
    IRenderInfo* mp_renderer; 
    IStateChanger* mp_state_changer;

    bool m_going_up;
    int m_previous_color_value;
    int m_color_value;
};

#endif // MAIN_MENU_STATE_H
