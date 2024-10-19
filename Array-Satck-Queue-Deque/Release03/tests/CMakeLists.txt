# Include google test
include(FetchContent)

# Download google test from its url on github
FetchConetne_Declare (
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# make sure that linking of the project and google test uses the same linking way(static or dynamic)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# build google test and enable it to be linked with the tests
FetchContent_MakeAvailable(googletest)

# add test executable with name lib_test
# compiles lib_test.cpp into lib_test.exe to be used later to run the tests
add_executable(lib_test ArrayTest.cpp StackTest.cpp QueueTest.cpp DequeTest.cpp)
# link google test libs with lib_test.cpp file allowing to use lib functions such as TEST and EXPECT_EQ
target_link_directories(lib_test gtest gtest_main)

# include current dir.(tests) and src dir. when looking for headers as
# headers of src dir. will need to be included in testing
target_link_directories(lib_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../src)

# integrate unit testing within the build provess where we can use ctest to ensure the functions are working as expected.
add_test(NAME lib_test COMMAND lib_test)