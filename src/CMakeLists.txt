set( SOURCES
     main.cpp
)

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
    tstsrl
    ${SOURCES}
)

set_target_properties(tstsrl PROPERTIES COMPILE_FLAGS "${SDL_CFLAGS}" LINK_FLAGS "${SDL_LFLAGS}")
target_link_libraries(tstsrl SDL2) 
