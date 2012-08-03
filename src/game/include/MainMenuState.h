#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "SDL.h"

#include "State.h"

class MainMenuState : public State {
public:
    MainMenuState(SDL_Renderer* pRenderer);    

    virtual void start();
    
    virtual bool event(SDL_Event* event);
    virtual bool capture();
    virtual bool update(double t, double dt);
    virtual bool render(double alpha);

private:
   
    SDL_Renderer* m_pRenderer; 
    bool m_going_up;
    int m_previous_color_value;
    int m_color_value;
};

#endif // MAIN_MENU_STATE_H
