set( SOURCES
     src/main.cpp
)

include_directories("../engine/include")

set(TARGET "game")

if (${TARGET_OS} MATCHES "android")

  set (SRC_STR "")
  foreach(SRC ${SOURCES})
    set(SRC_STR "${SRC_STR} \\\n  \$(SRC_PATH)/${SRC}")
  endforeach(SRC)

  configure_file(
    "${PROJECT_SOURCE_DIR}/platform_specific/android/jni/src/Android.mk.in"
    "${PROJECT_SOURCE_DIR}/platform_specific/android/jni/src/Android.mk"
  )

  return()
endif(${TARGET_OS} MATCHES "android")

add_executable (
    ${TARGET} 
    WIN32
    ${SOURCES}
)

if (${TARGET_OS} MATCHES "windows")

    target_link_libraries(${TARGET} SDL SDLmain)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/platform_specific/windows/sdl/lib/SDL.dll"
        $<TARGET_FILE_DIR:tstsrl>)
        
else (${TARGET_OS} MATCHES "windows")
    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "${SDL_CFLAGS}" LINK_FLAGS "${SDL_LFLAGS}")
    target_link_libraries(${TARGET} SDL2 engine) 
endif (${TARGET_OS} MATCHES "windows")
