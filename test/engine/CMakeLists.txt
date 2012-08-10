enable_testing()

add_executable(engine_ut
    src/test_looper.cpp
    )

include_directories(include
                    ../../src/engine/include
                    ../gmock/gtest/include
                    ../gmock/include)

target_link_libraries(engine_ut gmock gtest gtest_main engine)

if (${TARGET_OS} MATCHES "windows")
    target_link_libraries(engine_ut SDL)
else (${TARGET_OS} MATCHES "windows")
    set_target_properties(engine_ut PROPERTIES
                                    COMPILE_FLAGS "${SDL_CFLAGS}"
                                    LINK_FLAGS "${SDL_LFLAGS}")

    target_link_libraries(engine_ut SDL2)
endif (${TARGET_OS} MATCHES "windows")

add_test(NAME engine_ut
         COMMAND engine_ut)
