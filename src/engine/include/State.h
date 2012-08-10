#ifndef STATE_H
#define STATE_H

class State {
public:
    virtual void init() {};
//    virtual void prepare() {};
    virtual void start() {};
    virtual void stop() {};
//    virtual void release() {};
    virtual void shutdown() {};

    virtual bool event(SDL_Event*) { return false; };
    virtual bool capture() { return false; };
    virtual bool update(double t, double dt) { return false; };
    virtual bool render(double alpha) { return false; };
};

#endif // STATE_H
