#ifndef COMMAND_H
#define COMMAND_H

/** \file */

/**
  The enum of all different command types.
*/
enum CommandType {
    NO_COMMAND,     /**< There is no command in the queue; There is no type associated with the command. */

    MENU_UP,        /**< Go UP in a menu; No associated type. */
    MENU_DOWN,      /**< Go DOWN in a menu; No associated type. */
    MENU_SELECT,    /**< Select the current option in a menu; No associated type. */
    MENU_BACK,      /**< Go back in a MENU; No associated type. */

    EXTENDED        /**< Custom command; Associated type is CommandExtended extended. */
};

/**
  The Command to use when the engine doesn't provide an appropriate command. The type field
  allows you to define your own custom types. Use the code and data fields as you feel is
  appropriate!
*/
struct CommandExtended {
    int type;       /**< A user defined type field. */
    int code;       /**< A user defined code. */
    void* data1;    /**< A user defined data field. */
    void* data2;    /**< A BONUS user defined data field. */
};

/**
  The main struct that holds all other commands. Check the CommandType and use
  that to decide which field in the union to use.
*/
struct Command {
    /**
      The type to use to select which of the other fields to use.
    */
    CommandType type;               

    union {
        CommandExtended extended;   /**< The extended type to use with the type EXTENDED. */
    };
};
#endif // COMMAND_H

