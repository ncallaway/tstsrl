#ifndef MOCK_LOOP_MODERATOR
#define MOCK_LOOP_MODERATOR

#include "gmock/gmock.h"

#include "Looper.h"
#include "SDL.h"

class MockLoopModerator : public ILoopModerator {
public:
    MOCK_METHOD0(iterate, bool());
    MOCK_METHOD1(event, bool(SDL_Event* event));
    MOCK_METHOD0(capture, bool());
    MOCK_METHOD2(update, bool(double t, double dt));
    MOCK_METHOD1(render, bool(double alpha));
};

#endif // MOCK_LOOP_MODERATOR
