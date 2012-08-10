#ifndef I_STATE_CHANGER_H
#define I_STATE_CHANGER_H

/**
  An interface for a class capable of changing states.
*/
class IStateChanger {
public:
    virtual ~IStateChanger() {};

    /**
      Select the next state to use based on a given state_name. How state_names are determined is based
      on your state system. The default StateManager, for example, requires you to register states ahead of time, before
      they can be used.

      It is strongly encouraged that you use an enum instead of define'd ints to set the state values.
    
      \param state_name the value of the state to changed to.
    */
    virtual void set_next_state(int state_name) = 0;
};
#endif // I_STATE_CHANGER_H
