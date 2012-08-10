#ifndef ENGINE_EXCEPTION_H
#define ENGINE_EXCEPTION_H

#include <stdexcept>
#include <string>

/**
  An exception raised by the game engine. Hooray!
*/
class EngineException : public std::runtime_error {
public:
    /**
      \param [in] err The string message to display in the exception.
    */
    EngineException( const std::string &err ) : std::runtime_error( err ) { }
};
#endif // ENGINE_EXCEPTION_H

