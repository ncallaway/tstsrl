#ifndef COMMAND_QUEUE
#define COMMAND_QUEUE

#include <queue>

struct Command;

/**
  A queue of Commands that can be attached to a data model. This is the temporary
  storage for Commands that have been generated by an input device (or AI) that have
  not yet been processed.

  The CommandQueue delivers commands in a FIFO ordering.

  Generally the CommandQueue should be fully emptied on each frame, and all commands
  applied if possible.
*/
class CommandQueue {

public:

    /**
      Push a command onto the CommandQueue. This should usually be done by an input
      handler, or by an AI processor.

      \param command the Command to push onto the CommandQueue.
    */
    void push_command(Command command);

    /**
      Pull a command from the CommandQueue if it's not empty. If the CommandQueue is empty
      this will return a command of type NO_COMMAND.

      \return the oldest Command that was inserted into the queue, or a Command of type NO_COMMAND
      if the queue is empty.
    */
    Command pull_command();

    /**
      Return whether the CommandQueue has any outstanding Commands waiting inside it. A common use case will be:

          while (!command_queue.is_empty()) {
              Command cmd = command_queue.pull_command();
              process_command(cmd);
          }

      \return True if the CommandQueue is empty. False, otherwise.
    */
    bool is_empty();

private:
    std::queue<Command> m_queue;
};

#endif // COMMAND_QUEUE
