enable_testing()

add_executable(engine_ut
    src/test_looper.cpp
    src/test_state_manager.cpp
    )

include_directories(include
                    ../../src/engine/include
                    ../gmock/gtest/include
                    ../gmock/include)

target_link_libraries(engine_ut gmock gtest gtest_main engine)

if (${TARGET_OS} MATCHES "windows")
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)
    target_link_libraries(engine_ut SDL)
else (${TARGET_OS} MATCHES "windows")
    set_target_properties(engine_ut PROPERTIES
                                    COMPILE_FLAGS "${SDL_CFLAGS}"
                                    LINK_FLAGS "${SDL_LFLAGS}")

    target_link_libraries(engine_ut SDL2)
endif (${TARGET_OS} MATCHES "windows")

add_test(NAME engine_ut
         COMMAND engine_ut)
