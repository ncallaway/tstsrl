#ifndef ENGINE_EXCEPTION_H
#define ENGINE_EXCEPTION_H

#include <stdexcept>
#include <string>

class EngineException : public std::runtime_error {
public:
    EngineException( const std::string &err ) : std::runtime_error( err ) { }
};
#endif // ENGINE_EXCEPTION_H

