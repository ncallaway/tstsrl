#ifndef LOOPER_H
#define LOOPER_H

#include "SDL.h"

/**
  The interface that contains the callback functions that the Looper will call while executing its loop. Each
  of these functions may be called once (or more) per frame. For a detailed understanding of why the functions
  are ordered this way see [Fix your Timestep!](http://gafferongames.com/game-physics/fix-your-timestep/).

  Any of these functions can return True to terminate the loop.
*/
class ILoopModerator {
public:
    virtual ~ILoopModerator() {}

    /**
      Called once per iteration of the loop. This is the first function called at the beginning of each loop.

      \return True to terminate the loop. False to continue it!
    */
    virtual bool iterate() = 0;

    /**
      Called when processing events from the event loop. Note that this may be called multiple times per frame, and will usually completely
      empty the event queue on each iteration. Thus, the event processing should be as fast as possible.

      \param event The event that should be processed. Handle with caution! See [SDL_Event](http://wiki.libsdl.org/moin.cgi/SDL_Event?highlight=%28%5CbCategoryStruct%5Cb%29%7C%28CategoryEvents%29%7C%28SGStructures%29)
      for more details about the parameter.
      \return True to terminate the loop. False to continue it!
    */
    virtual bool event(SDL_Event* event) = 0;

    /**
      Called before an update-render cycle to "capture" necessary values as previously rendered. All values that should vary smoothly from frame
      to frame should be captured by this method.

      The values that are captured here should be interpolated with the current values by the render() funciton.
      \return True to terminate the loop. False to continue it!
    */
    virtual bool capture() = 0;

    /**
      Perform the any updates necessary. Physics, AI, input handling, etc.

      \param t The total time elapsed in seconds since the beginning of the loop.
      \param dt The time elapsed in seconds since the last update().
      \return True to terminate the loop. False to continue it!
    */
    virtual bool update(double t, double dt) = 0;

    /**
      Do the rendering! This should use the alpha parameter to interpolate "captured" values and present values:

          render_value = current_value*alpha + previous_value*(1-alpha)

      \param alpha The blend paramter that describes how much to interpolate between "captured" values and present values.
      \return True to terminate the loop. False to continue it!
    */
    virtual bool render(double alpha) = 0;
};

/**
  The configuration that a looper should use.
*/
struct LooperConfiguration {
    /**
      The ILoopModerator that contains the functions that the Looper will call during the
      game loop.
    */
    ILoopModerator* loop_moderator;

    /**
      The amount of time in seconds that the Looper should use for each update timestep. The Looper will call
      the update function for as many update_dt timespans as it can fit since the last rendered frame.

      That is, if update_dt is .1s and .5s have elapsed since the last frame, we will call update 5 times,
      with .1s dt for each update. 
    */
    double update_dt;

    /**
      The maximum amount of time in seconds to spend updating per one frame. If the time since the last frame
      was 1s, and the max_frame_time is .25s, then we will only add .25s to the amount of time to simulate.
      This prevents spikes of poor performance from cascading forward.
    */
    double max_frame_time;
};

/**
  A class that performs a continuous loop, and dispatches callbacks to the appropriate functions.
  The implementation of the loop in Looper is very similar to the final loop listed in
  [Fix your timestep](http://gafferongames.com/game-physics/fix-your-timestep/).

  The key elements of this loop are:
  - Pumps the SDL Event queue.
  - A fixed update timestep.
  - A maximum update time per frame (to prevent performance issues to accumulate over time).
  - Iterpolated rendering (to prevent temporal aliasing).

  To properly use the looper, you will need to provide an ILoopModerator. The StateManager is
  one such implementation. Create a LooperConfiguration that refers to the desired ILoopModerator and
  setup the looper with set_configuration(). Finally, calling loop() will execute the loop!
*/
class Looper {

public:

    Looper();

    /**
      Set the configuration that this Looper should use. Note that the 
      looper will ignore changes to the configuration's dt parameter until
      the next iteration of the loop if it is currently running.

      \param configuration The LooperConfiguration to use for the looper. If
      the configuration is invalid in some way, the looper will exit if
      it's currently looping.
    */
    void set_configuration(LooperConfiguration configuration);

    /**
      Loop! The looper takes over and loops indefinitely, until it receieves
      a bad configuration, or one of its callbacks instructs it to terminate.
    */
    void loop(); 

private:
   
    bool is_configuration_valid();

    LooperConfiguration m_configuration;
};

#endif // LOOPER_H
