cmake_minimum_required(VERSION 3.15)
project(Release02)

# Enable testing
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include subdirectories
add_subdirectory(List)
add_subdirectory(LinearDS)
add_subdirectory(tests)

# Download Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
