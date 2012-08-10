#ifndef LOOPER_H
#define LOOPER_H

#include "SDL.h"

class ILoopModerator {
public:
    virtual ~ILoopModerator() {}

    virtual bool iterate() = 0;
    virtual bool event(SDL_Event* event) = 0;
    virtual bool capture() = 0;
    virtual bool update(double d, double dt) = 0;
    virtual bool render(double alpha) = 0;
};

struct LooperConfiguration {
    ILoopModerator* loop_moderator;

    double update_dt;
    double max_frame_time;
};

class Looper {

public:

    Looper();

    void set_configuration(LooperConfiguration configuration);

    void loop(); 

private:
   
    bool is_configuration_valid();

    LooperConfiguration m_configuration;
};

#endif // LOOPER_H
