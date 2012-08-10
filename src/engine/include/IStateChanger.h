#ifndef I_STATE_CHANGER_H
#define I_STATE_CHANGER_H

class IStateChanger {
public:
    virtual ~IStateChanger() {};

    virtual void set_next_state(int state_name) = 0;
};
#endif // I_STATE_CHANGER_H
