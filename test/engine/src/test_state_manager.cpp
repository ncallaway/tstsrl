#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EngineException.h"
#include "MockState.h"
#include "StateManager.h"

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Test;

class StateManagerTest : public Test {
public:
    NiceMock<MockState> m_mock1;
    NiceMock<MockState> m_mock2;
    NiceMock<MockState> m_mock3;

    StateManager* mp_state_manager;

    virtual void SetUp() {
        mp_state_manager = new StateManager();
    }

    virtual void TearDown() {
        delete mp_state_manager;
    }
};

TEST_F(StateManagerTest, SetNextState_Registered) {
    mp_state_manager->register_state(1, &m_mock1);
    
    EXPECT_NO_THROW(mp_state_manager->set_next_state(1));

    mp_state_manager->iterate();
}

TEST_F(StateManagerTest, SetNextState_Unregistered) {
    EXPECT_THROW(mp_state_manager->set_next_state(1), EngineException);
}

TEST_F(StateManagerTest, SetNextState_Null) {
    mp_state_manager->register_state(1, NULL);
    
    EXPECT_THROW(mp_state_manager->set_next_state(1), EngineException);
}

TEST_F(StateManagerTest, SetNextState_CorrectState) {
    EXPECT_CALL(m_mock1, start())
        .Times(1);

    mp_state_manager->register_state(1, &m_mock1);

    mp_state_manager->set_next_state(1);

    mp_state_manager->iterate();
}

TEST_F(StateManagerTest, SetNextState_ReregisteredCorrectState) {
    EXPECT_CALL(m_mock1, start())
        .Times(0);
    EXPECT_CALL(m_mock3, start())
        .Times(1);

    mp_state_manager->register_state(1, &m_mock1);
    mp_state_manager->register_state(1, &m_mock3);

    mp_state_manager->set_next_state(1);

    mp_state_manager->iterate();
}

TEST_F(StateManagerTest, ReleaseStates) {
    mp_state_manager->register_state(1, &m_mock3);
    mp_state_manager->set_next_state(1);

    mp_state_manager->release_states();
    EXPECT_THROW(mp_state_manager->set_next_state(1), EngineException);
};

TEST_F(StateManagerTest, Iterate_NoState) {
    ASSERT_TRUE(mp_state_manager->iterate());
}

TEST_F(StateManagerTest, Iterate_AnyState) {
    mp_state_manager->register_state(1, &m_mock1);
    mp_state_manager->set_next_state(1);
    ASSERT_FALSE(mp_state_manager->iterate());
}

TEST_F(StateManagerTest, Iterate_StartOnce) {
    EXPECT_CALL(m_mock1, start())
        .Times(1);

    mp_state_manager->register_state(1, &m_mock1);
    mp_state_manager->set_next_state(1);

    mp_state_manager->iterate();
    mp_state_manager->iterate();
}

TEST_F(StateManagerTest, Iterate_Stop) {
    InSequence dummy;

    EXPECT_CALL(m_mock1, start())
        .Times(1);
    EXPECT_CALL(m_mock1, stop())
        .Times(1);
    EXPECT_CALL(m_mock2, start())
        .Times(1);

    mp_state_manager->register_state(1, &m_mock1);
    mp_state_manager->register_state(2, &m_mock2);

    mp_state_manager->set_next_state(1);
    mp_state_manager->iterate();
    mp_state_manager->iterate();
    mp_state_manager->iterate();

    mp_state_manager->set_next_state(2);
    mp_state_manager->iterate();
}
