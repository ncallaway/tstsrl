set( SOURCES
     src/main.cpp
     src/MainMenuState.cpp
     src/ControllerSelectState.cpp
     src/GameState.cpp
)

set( INCLUDE_DIRS
     "../engine/include"
     "include"
   )

include_directories(${INCLUDE_DIRS})

set(TARGET "game")

if (${TARGET_OS} MATCHES "android")

  set (SRC_STR "")
  foreach(SRC ${SOURCES})
    set(SRC_STR "${SRC_STR} \\\n  \$(SRC_PATH)/${SRC}")
  endforeach(SRC)

  set (INCLUDE_STR "")
  foreach(DIR ${INCLUDE_DIRS})
    set(INCLUDE_STR "${INCLUDE_STR}  \\\n  ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}")
  endforeach(DIR)


  configure_file(
    "${PROJECT_SOURCE_DIR}/platform_specific/android/jni/src/game/Android.mk.in"
    "${PROJECT_SOURCE_DIR}/platform_specific/android/jni/src/game/Android.mk"
  )

  return()
endif(${TARGET_OS} MATCHES "android")

add_executable (
    ${TARGET} 
    WIN32
    ${SOURCES}
)

if (${TARGET_OS} MATCHES "windows")

    target_link_libraries(${TARGET} SDL SDL2_ttf SDLmain engine)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/platform_specific/windows/sdl/lib/SDL.dll"
        $<TARGET_FILE_DIR:${TARGET}>)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/platform_specific/windows/sdl/lib/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${TARGET}>)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/platform_specific/windows/sdl/lib/libfreetype-6.dll"
        $<TARGET_FILE_DIR:${TARGET}>)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/platform_specific/windows/sdl/lib/zlib1.dll"
        $<TARGET_FILE_DIR:${TARGET}>)
        
else (${TARGET_OS} MATCHES "windows")
    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "${SDL_CFLAGS}" LINK_FLAGS "${SDL_LFLAGS}")
    target_link_libraries(${TARGET} SDL2 SDL2_ttf engine) 
endif (${TARGET_OS} MATCHES "windows")
