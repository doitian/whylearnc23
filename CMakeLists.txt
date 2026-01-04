cmake_minimum_required(VERSION 3.25)
project(whylearnc23 LANGUAGES C)

# Set C23 standard for GCC/Clang, use latest standard for MSVC
if(MSVC)
    # MSVC doesn't have a C23 flag yet, use /std:clatest for latest C features
    # Set to C17 as the standard, but add /std:clatest as a compile option
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)
    add_compile_options(/std:clatest)
else()
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)
endif()

# Enable testing
enable_testing()

# Add libraries
add_subdirectory(libs/string)

# Build tests if enabled
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()