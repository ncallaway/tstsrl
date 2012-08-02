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

    while ( !quit ) {
        double dt = m_configuration.update_dt;

        double current_time = (double)SDL_GetTicks() / 1000.0;
        double elapsed_time = current_time - previous_time;

        if (elapsed_time > m_configuration.max_frame_time) {
            elapsed_time = m_configuration.max_frame_time;
        }

        previous_time = current_time;
        accumulator += elapsed_time;

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

        const double alpha = accumulator / dt;
        
        if (m_configuration.render_function != NULL && !quit) {
            quit |= m_configuration.render_function(alpha);
        }
    }
}
