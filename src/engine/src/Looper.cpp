#include "Looper.h"

#include <stdio.h>

Looper::Looper() {
    m_configuration.loop_moderator = NULL;
    m_configuration.update_dt = 0;
    m_configuration.max_frame_time = 0;
}

void Looper::set_configuration(LooperConfiguration configuration) {
    m_configuration = configuration;
}

void Looper::loop() {
    bool quit = false;


    double t = 0;
    double accumulator = 0.0;
    double previous_time = (double)SDL_GetTicks() / 1000.0;
    SDL_Event event;

    while ( !quit ) {
        quit |= !is_configuration_valid();

        quit |= m_configuration.loop_moderator->iterate();
        quit |= !is_configuration_valid();

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
            quit |= m_configuration.loop_moderator->event(&event);
            quit |= !is_configuration_valid();
        }

        // Perform as many updates as we can!
        while (accumulator >= m_configuration.update_dt && !quit) {
            quit |= m_configuration.loop_moderator->capture();
            quit |= !is_configuration_valid();

            quit |= m_configuration.loop_moderator->update(t, dt);
            quit |= !is_configuration_valid();

            t += dt;
            accumulator -= dt;
        }

        // And render.
        const double alpha = accumulator / dt;

        quit |= m_configuration.loop_moderator->render(alpha);
        quit |= !is_configuration_valid();
    }
}

bool Looper::is_configuration_valid() {
    if (m_configuration.loop_moderator == NULL ||
        m_configuration.update_dt == 0 ||
        m_configuration.max_frame_time == 0) {

        return false;
    }

    return true;
}
