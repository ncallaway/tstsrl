#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>

#include "Looper.h" // Required for subclass of ILoopModerator
#include "IStateChanger.h" // Required for subclass of IStateChanger

class State;

/**
  The default class to perform state management, and moderate the loop handler.

  A simple implementation of the state manager will be to register several states, set
  the next state as your introductory state, set up the StateManager in the LooperConfiguration to
  be the ILoopModerator, and the call Looper.loop().
*/
class StateManager : public ILoopModerator, public IStateChanger {
public:
    StateManager();

    /**
      Register a state with the StateManager. This **must** be done before any state can call
      set_next_state() using the state name. Calling set_next_state() before registering the state
      will generate an exception.

      It is strongly encourage to use an enum instead of #define'd ints to define the state names.
      
      \param state_name The name of the state. If this is an already registered State, the old State pointer
      will be forgotten.
      \param state A pointer to the State to use when set_next_state is called.
    */
    void register_state(int state_name, State* state);
    
    /**
      Release all the currently held State pointers. After calling this, all states will be unregistered, and
      it would be an error to call set_next_state(). If you want to set states after calling this function, the
      states will need to be re-registered via register_state().
    */
    void release_states();

    void set_next_state(int state_name);

    virtual bool iterate();
    virtual bool event(SDL_Event* event);
    virtual bool capture();
    virtual bool update(double d, double dt);
    virtual bool render(double alpha);

private:
    State* get_registered_state(int state_name);

    State* mp_current_state;
    State* mp_next_state;

    std::map<int, State*> m_states; 
};

#endif // STATE_MANAGER_H
