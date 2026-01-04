cmake_minimum_required(VERSION 3.25)
project(whylearnc23 LANGUAGES C)

# Set C23 standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# MSVC needs special flag for C23 support (experimental)
if(MSVC)
    add_compile_options(/std:clatest)
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