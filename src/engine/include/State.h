#ifndef STATE_H
#define STATE_H

union SDL_Event;

/**
  The State class defines a game state that controls the game loop. Examples of States might be:

  - Menus
  - Gameplay
  - Loading Screens
 
  The State class defines two important components. **Lifecycle** methods and **Game loop** methods. The
  lifecycle methods are called at important times for the state: creation, transitioning, starting, stopping, etc.
  while the game loop methods are called once (or several) times for each iteration of the game loop while the
  state is active.
 
  All game loop methods return a boolean parameter that determines if the game should exit as a result of the
  call. Return true to exit the game loop, false to keep going. By default, all methods return false.
*/
class State {
public:
    /**
      Called when the State is being initialized. Each state should be initialized *once* for the lifecycle of
      the state (usually at the start of the program).
    */  
    virtual void init() {}; 

//    virtual void prepare() {};

    /**
      Called when the state is about to become active. After this method is complete, the state may receive calls
      to its game loop functions below.
     */
    virtual void start() {};
    /**
      Called when the state is about to stop being active. The game will no longer receive game loop calls (and can
      release any resources it needs for the game loop).
    */
    virtual void stop() {};

//    virtual void release() {};

    /**
      The state is about to be shutdown. The object will no longer be used at all, and can dispose of any resources it
      is holding onto.
    */
    virtual void shutdown() {};

    /**
      The event function is called when an event is receieved in the game loop. Events are the first thing
      processed in the game loop, and are usually processed fully before the event loop contiues. Therefore,
      event handling should be done quickly, and should avoid "expensive" tasks.

      \param [in] event The SDL_Event to process.
      \return True to exit the game loop. False to continue.
    */
    virtual bool event( SDL_Event* event ) { return false; };

    /**
      The capture function is called to capture any values that change smoothly over time. The previous values
      will be used in conjunction with the current values to interpolate between two frames to remove any temporal
      aliasing.

      \return True to exit the game loop. False to continue.
    */
    virtual bool capture() { return false; };

    /**
      Update the state for a single iteration.

      \param [in] t the total amount of time that the game has been looping for.
      \param [in] dt the amount of time elapsed since the last call to update. 
      \return True to exit the game loop. False to continue.
    */
    virtual bool update( double t, double dt ) { return false; };
    /**
      Render the state, interpolating between the previous state and the current state using the alpha parameter.

      \param [in] alpha the blend factor. To properly interpolate use:

          value = current*alpha + previous*(1-alpha)
      \return True to exit the game loop. False to continue.
    */
    virtual bool render( double alpha ) { return false; };
};

#endif // STATE_H
