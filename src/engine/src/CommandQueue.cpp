#include "CommandQueue.h"
#include "Command.h"

void CommandQueue::push_command(Command command) {
    m_queue.push(command);
}

Command CommandQueue::pull_command() {
    Command result;

    if (m_queue.empty()) {
        result.type = NO_COMMAND;
    } else {
        result = m_queue.front();
        m_queue.pop();
    }

    return result;
}

bool CommandQueue::is_empty() {
    return m_queue.empty();
}
