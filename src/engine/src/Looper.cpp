#include "Looper.h"

#include <stdio.h>

Looper::Looper() {
    m_configuration.capture_function = NULL;
    m_configuration.update_function = NULL;
    m_configuration.render_function = NULL;
    m_configuration.update_dt = 0;
    m_configuration.max_frame_time = 0;
}

void Looper::set_configuration(LooperConfiguration configuration) {
    m_configuration = configuration;
}

void Looper::loop() {
    bool quit = false;

    if (m_configuration.update_function == NULL ||
        m_configuration.update_dt == 0 ||
        m_configuration.max_frame_time == 0) {

        quit = true;
    }

    double t = 0;
    double accumulator = 0.0;
    double previous_time = (double)SDL_GetTicks() / 1000.0;
    SDL_Event event;

    while ( !quit ) {

        // Capture dt for this iteration. It should be constant for a full iteration of the loop.
        double dt = m_configuration.update_dt;

        // Keep track of various time values.
        double current_time = (double)SDL_GetTicks() / 1000.0;
        double elapsed_time = current_time - previous_time;

        if (elapsed_time > m_configuration.max_frame_time) {
            elapsed_time = m_configuration.max_frame_time;
        }

        previous_time = current_time;
        accumulator += elapsed_time;

        // Handle all events.
        while (SDL_PollEvent(&event)) {
            if (m_configuration.event_function != NULL) {
                quit |= m_configuration.event_function(&event);
            }
        }

        // Perform as many updates as we can!
        while (accumulator >= m_configuration.update_dt && !quit) {

            if (m_configuration.capture_function != NULL) {
                quit |= m_configuration.capture_function();
            }

            if (m_configuration.update_function != NULL) {
                quit |= m_configuration.update_function(t, dt);
            }

            t += dt;
            accumulator -= dt;
        }

        // And render.
        const double alpha = accumulator / dt;

        if (m_configuration.render_function != NULL && !quit) {
            quit |= m_configuration.render_function(alpha);
        }
    }
}
