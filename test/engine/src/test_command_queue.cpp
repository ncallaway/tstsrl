#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CommandQueue.h"
#include "Command.h"

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Test;

class CommandQueueTest : public Test {
public:
    CommandQueue* mp_command_queue;

    virtual void SetUp() {
        mp_command_queue = new CommandQueue();
    }

    virtual void TearDown() {
    } 
};

TEST_F(CommandQueueTest, PushCommand) {
    Command cmd;

    cmd.type = MENU_UP;

    mp_command_queue->push_command(cmd);

    ASSERT_EQ(MENU_UP, mp_command_queue->pull_command().type);
}

TEST_F(CommandQueueTest, PullCommand_Ordering) {
    Command cmd;
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);
    cmd.type = MENU_DOWN;
    mp_command_queue->push_command(cmd);
    cmd.type = MENU_SELECT;
    mp_command_queue->push_command(cmd);

    ASSERT_EQ(MENU_UP, mp_command_queue->pull_command().type);
    ASSERT_EQ(MENU_DOWN, mp_command_queue->pull_command().type);
    ASSERT_EQ(MENU_SELECT, mp_command_queue->pull_command().type);
}

TEST_F(CommandQueueTest, PullCommand_Empty) {
    Command cmd;
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);
    cmd.type = MENU_DOWN;
    mp_command_queue->push_command(cmd);

    mp_command_queue->pull_command();
    mp_command_queue->pull_command();
    ASSERT_EQ(NO_COMMAND, mp_command_queue->pull_command().type);
}

TEST_F(CommandQueueTest, IsEmpty_NoCommands) {
    ASSERT_TRUE(mp_command_queue->is_empty());
}

TEST_F(CommandQueueTest, IsEmpty_NotEmpty) {
    Command cmd;
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);

    ASSERT_FALSE(mp_command_queue->is_empty());
}

TEST_F(CommandQueueTest, IsEmpty_Emptied) {
    Command cmd;
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);

    mp_command_queue->pull_command();
    ASSERT_TRUE(mp_command_queue->is_empty());
}

TEST_F(CommandQueueTest, NormalUse) {
    Command cmd;
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);
    cmd.type = MENU_UP;
    mp_command_queue->push_command(cmd);

    while (!mp_command_queue->is_empty()) {
        ASSERT_EQ(MENU_UP, mp_command_queue->pull_command().type);
    }

    ASSERT_EQ(NO_COMMAND, mp_command_queue->pull_command().type);
}
