#ifndef MOCK_STATE_H
#define MOCK_STATE_H

#include "gmock/gmock.h"

#include "State.h"
#include "SDL.h"

class MockState : public State {
public:
    MOCK_METHOD0(init, void());
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD0(shutdown, void());

    MOCK_METHOD1(event, bool(SDL_Event* event));
    MOCK_METHOD0(capture, bool());
    MOCK_METHOD2(update, bool(double t, double dt));
    MOCK_METHOD1(render, bool(double alpha));
};
#endif // MOCK_STATE_H
