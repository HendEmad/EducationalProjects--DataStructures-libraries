# Include Google Test
include(FetchContent)

# Download Google Test from GitHub
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Ensure static linking with Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Build and make Google Test available
FetchContent_MakeAvailable(googletest)

# Add the test executable with test files
add_executable(lib_test ArrayTest.cpp StackTest.cpp QueueTest.cpp DequeTest.cpp)

# Link Google Test and ArrayLib with the test executable
target_link_libraries(lib_test PRIVATE gtest gtest_main ArrayLib)

# Include src directory to locate headers for ArrayLib
target_include_directories(lib_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../src)

# Integrate ctest
add_test(NAME lib_test COMMAND lib_test)


# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(lib_test)