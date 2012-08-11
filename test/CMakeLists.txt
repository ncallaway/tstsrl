enable_testing()

set(BUILD_SHARED_LIBS 1)
add_subdirectory(gmock)
add_subdirectory(engine)

#if (${TARGET_OS} MATCHES "windows")
    # For MSVC, CMake sets certain flags to defaults we want to override.
    # This replacement code is taken from sample in the CMake Wiki at
    # http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace.
#    message("I'm awesome")
#    foreach (flag_var
#             CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
#             CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
             
#        string(REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
#    endforeach()
#endif (${TARGET_OS} MATCHES "windows")