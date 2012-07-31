cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

project(tstsrl)

set(TARGET_OS ${CMAKE_SYSTEM_NAME})
string(TOLOWER ${TARGET_OS} TARGET_OS)

if (${ANDROID} MATCHES "y")
    set(TARGET_OS "android")
endif(${ANDROID} MATCHES "y")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${TARGET_OS})

if (${TARGET_OS} MATCHES "windows")
    include_directories("platform_specific/windows/sdl/include")
    link_directories("platform_specific/windows/sdl/lib")
else (${TARGET_OS} MATCHES "windows")
    find_program(SDL2_CONFIG sdl2-config)

    if ("{SDL2_CONFIG}" STREQUAL "SDL2_CONFIG-NOTFOUND")
        message(FATAL_ERROR "sdl2-config could not be found. Be sure to install SDL2.")
    endif ("{SDL2_CONFIG}" STREQUAL "SDL2_CONFIG-NOTFOUND")

    execute_process(COMMAND ${SDL2_CONFIG} --cflags OUTPUT_VARIABLE SDL_CFLAGS)
    execute_process(COMMAND ${SDL2_CONFIG} --libs OUTPUT_VARIABLE SDL_LFLAGS)

    string(REPLACE "\n" "" SDL_CFLAGS ${SDL_CFLAGS})
    string(REPLACE "\n" "" SDL_LFLAGS ${SDL_LFLAGS})
endif (${TARGET_OS} MATCHES "windows")


add_subdirectory(src)
