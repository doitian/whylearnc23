# Why Learn C23 - Multi-Library Project

A C23 project demonstrating modern C development with multiple standalone libraries, using Conan for dependency management and libcheck for testing.

## Project Structure

```
whylearnc23/
├── CMakeLists.txt          # Root CMake configuration
├── conanfile.txt           # Conan dependencies
├── libs/                   # Standalone libraries
│   └── string/             # String utility library
└── tests/                  # Test suites
```

## Requirements

- **CMake** 3.25 or later
- **Conan** 2.x package manager
- **C Compiler** with C23 support:
  - GCC 13+ (recommended)
  - Clang 16+
  - MSVC 19.35+ (Visual Studio 2022 17.5+)

## Setup and Build

### 1. Install Conan (if not already installed)

```bash
pip install conan
```

### 2. Configure Conan Profile

```bash
conan profile detect --force
```

### 3. Install Dependencies

```bash
conan install . --build=missing
```

### 4. Configure CMake

#### On Windows (Visual Studio):
```bash
cmake --preset conan-default
```

#### On Linux/macOS:
```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```

### 5. Build the Project

```bash
cmake --build build --config Release
```

### 6. Run Tests

#### Using CTest (recommended):

```bash
# Windows
ctest --test-dir build -C Release --output-on-failure

# Linux/macOS
ctest --test-dir build --output-on-failure
```

#### Or run the test executable directly:

```bash
# Windows
.\build\tests\string\Release\string_tests.exe

# Linux/macOS
./build/tests/string/string_tests
```

## Adding New Libraries

To add a new library to the project:

1. Create directory structure:
   ```
   libs/newlib/
   ├── CMakeLists.txt
   ├── include/
   │   └── newlib.h
   └── src/
       └── newlib.c
   ```

2. Add to root `CMakeLists.txt`:
   ```cmake
   add_subdirectory(libs/newlib)
   ```

3. Create test directory:
   ```
   tests/newlib/
   ├── CMakeLists.txt
   └── test_newlib.c
   ```

4. Add to `tests/CMakeLists.txt`:
   ```cmake
   add_subdirectory(newlib)
   ```

## Testing Framework

The project uses **libcheck (Check)** for unit testing. Check is a unit testing framework for C that provides a simple API for writing test cases. Each library has its own test suite that can be run independently or as part of the entire test suite.

### Writing Tests with Check

Check uses a simple macro-based API:

```c
START_TEST(test_name)
{
    // Your test code here
    ck_assert_int_eq(actual, expected);
    ck_assert_str_eq(str1, str2);
    ck_assert_ptr_nonnull(ptr);
}
END_TEST
```