cmake_minimum_required(VERSION 3.10)
project(DataStructuresLibrary)

# set cpp version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED True)

# Add source files will run on
add_subdirectory(src)
add_subdirectory(tests)

# enable testing
enable_testing()