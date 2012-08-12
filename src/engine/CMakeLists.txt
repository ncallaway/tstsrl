set( SOURCES
     src/Looper.cpp
     src/StateManager.cpp
     src/CommandQueue.cpp
   )

set( INCLUDE_DIRS
     "include"
   )

include_directories("include")

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
    "${PROJECT_SOURCE_DIR}/platform_specific/android/jni/src/engine/Android.mk.in"
    "${PROJECT_SOURCE_DIR}/platform_specific/android/jni/src/engine/Android.mk"
  )

  return()
endif(${TARGET_OS} MATCHES "android")

add_library( engine STATIC ${SOURCES} )

if (${TARGET_OS} MATCHES "windows")
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)
else (${TARGET_OS} MATCHES "windows")
    set_target_properties(engine PROPERTIES COMPILE_FLAGS "${SDL_CFLAGS}")
endif (${TARGET_OS} MATCHES "windows")
