#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>

#include "Looper.h" // Required for subclass of ILoopModerator
#include "IStateChanger.h" // Required for subclass of IStateChanger

class State;

class StateManager : public ILoopModerator, public IStateChanger {
public:
    StateManager();

    void register_state(int state_name, State* p_state);
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
