set( SOURCES
     src/Looper.cpp
   )

include_directories("include")

add_library( engine STATIC ${SOURCES} )

if (${TARGET_OS} MATCHES "windows")
       # Nothing yet... 
else (${TARGET_OS} MATCHES "windows")
    set_target_properties(engine PROPERTIES COMPILE_FLAGS "${SDL_CFLAGS}")
endif (${TARGET_OS} MATCHES "windows")
