#ifndef LOOPER_H
#define LOOPER_H

#include "SDL.h"

struct LooperConfiguration {
    bool (*event_function)(SDL_Event*);
    bool (*capture_function)();
    bool (*update_function)(double t, double dt);
    bool (*render_function)(double alpha);

    double update_dt;
    double max_frame_time;
};

class Looper {

public:

    Looper();

    void set_configuration(LooperConfiguration configuration);

    void loop(); 

private:

    LooperConfiguration m_configuration;
};

#endif // LOOPER_H
