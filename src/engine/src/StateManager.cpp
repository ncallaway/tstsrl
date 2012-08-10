#include "StateManager.h"

#include "State.h"
#include "EngineException.h"

StateManager::StateManager() {
    mp_current_state = NULL;
    mp_next_state = NULL;
}

void StateManager::register_state(int state_name, State* p_state) {
    m_states[state_name] = p_state;
}

void StateManager::release_states() {
    m_states.clear();
}

void StateManager::set_next_state(int state_name) {
    State* next_state = get_registered_state(state_name);

    if (next_state == NULL) {
        throw new EngineException("Attempted to change to an unregistered state.");
    }

    mp_next_state = next_state;
}

bool StateManager::iterate() {
    if (mp_next_state != NULL) {
        if (mp_current_state != NULL) {
            mp_current_state->stop();
        }

        mp_current_state = mp_next_state;
        mp_current_state->start();
    }

    mp_next_state = NULL;
    return (mp_current_state == NULL);
}

bool StateManager::event(SDL_Event* event) {
   return mp_current_state->event(event); 
}

bool StateManager::capture() {
    return mp_current_state->capture();
}

bool StateManager::update(double d, double dt) {
    return mp_current_state->update(d, dt);
}

bool StateManager::render(double alpha) {
    return mp_current_state->render(alpha);
}

State* StateManager::get_registered_state(int state_name) {
    std::map<int, State*>::iterator it;
    it = m_states.find(state_name);

//    if (it != m_states.end) {
//        return NULL;
//    }

    return it->second;
}
