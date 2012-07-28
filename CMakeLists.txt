cmake_minimum_required(VERSION 2.6)

project(tstsrl)

set(TARGET_OS ${CMAKE_SYSTEM_NAME})

if (${ANDROID} MATCHES "y")
    set(TARGET_OS "android")
endif(${ANDROID} MATCHES "y")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${TARGET_OS})

find_program(SDL2_CONFIG sdl2-config)

if ("{SDL2_CONFIG}" STREQUAL "SDL2_CONFIG-NOTFOUND")
    message(FATAL_ERROR "sdl2-config could not be found. Be sure to install SDL2.")
endif ("{SDL2_CONFIG}" STREQUAL "SDL2_CONFIG-NOTFOUND")

execute_process(COMMAND ${SDL2_CONFIG} --cflags OUTPUT_VARIABLE SDL_CFLAGS)
execute_process(COMMAND ${SDL2_CONFIG} --libs OUTPUT_VARIABLE SDL_LFLAGS)

string(REPLACE "\n" "" SDL_CFLAGS ${SDL_CFLAGS})
string(REPLACE "\n" "" SDL_LFLAGS ${SDL_LFLAGS})

add_subdirectory(src)
