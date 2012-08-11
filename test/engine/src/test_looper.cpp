#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MockLoopModerator.h"
#include "Looper.h"

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Test;

class LooperTest : public Test {
public:
    NiceMock<MockLoopModerator> m_mock;
    LooperConfiguration m_config;
    Looper* mp_looper;

    virtual void SetUp() {
        m_config.loop_moderator = &m_mock;
        m_config.update_dt = 0.00001;
        m_config.max_frame_time = 0.00002;

        mp_looper = new Looper();
        mp_looper->set_configuration(m_config);
    }
    
    virtual void TearDown() {
        delete mp_looper;
    }
};

TEST_F(LooperTest, IterateFirst) {
    InSequence dummy;

    EXPECT_CALL(m_mock, iterate())
        .Times(1);
    EXPECT_CALL(m_mock, render(_))
        .WillOnce(Return(true));

    mp_looper->loop();
}

TEST_F(LooperTest, ExitIterate) {
    EXPECT_CALL(m_mock, iterate())
        .WillOnce(Return(true));

    mp_looper->loop();
}

TEST_F(LooperTest, ExitCapture) {
    EXPECT_CALL(m_mock, capture())
        .WillOnce(Return(true));

    mp_looper->loop();
}

TEST_F(LooperTest, ExitUpdate) {
    EXPECT_CALL(m_mock, update(_,m_config.update_dt))
        .WillOnce(Return(true));

    mp_looper->loop();
}

TEST_F(LooperTest, ExitRender) {
    EXPECT_CALL(m_mock, render(_))
        .WillOnce(Return(true));

    mp_looper->loop();
}
