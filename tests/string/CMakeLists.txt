cmake_minimum_required(VERSION 3.25)

# Find Check test framework (CMake package name is Check, from libcheck Conan package)
find_package(Check REQUIRED)

# String library tests using Check framework
add_executable(string_tests
    test_string.c
)

target_link_libraries(string_tests
    PRIVATE
        string
        Check::check
)

# Add test to CTest
add_test(NAME string_tests COMMAND string_tests)