#ifndef CONTROLLER_SELECT_STATE_H
#define CONTROLLER_SELECT_STATE_H

#include "SDL.h"

#include "State.h" // Required for subclass of State

class IRenderInfo;
class IStateChanger;

/**
  The state responsible for displaying the controller select screen.
*/
class ControllerSelectState : public State {
public:
    /**
      \param [in] state_changer The IStateChanger that can change between various states.
      \param [in] renderer The IRenderInfo that contains the data necessary to render the menu.
    */
    ControllerSelectState(IStateChanger* state_changer, IRenderInfo* renderer);

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
#endif // CONTROLLER_SELECT_STATE_H
