set( SOURCES
     main.cpp
)

add_executable (
    tstsrl
    ${SOURCES}
)

set_target_properties(tstsrl PROPERTIES COMPILE_FLAGS "${SDL_CFLAGS}" LINK_FLAGS "${SDL_LFLAGS}")
target_link_libraries(tstsrl SDL2) 
