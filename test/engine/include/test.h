#include "gmock/gmock.h"

class ITest {
public:
    virtual ~ITest() {};

    virtual int get_test() = 0;
};

class MockTest : public ITest {
    MOCK_METHOD0(get_test, int());
};
