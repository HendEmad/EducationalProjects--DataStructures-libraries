set(TEST_SOURCES
    test_forward_list.cpp
    test_doubly_list.cpp
    test_circular_list.cpp
    test_stack.cpp
    test_queue.cpp
    test_deque.cpp
)

add_executable(Tests ${TEST_SOURCES})

# Link with the List & LinearDS libraries and Google Test
target_link_libraries(Tests PRIVATE List gtest gtest_main)

target_include_directories(Tests PRIVATE 
                            ${CMAKE_SOURCE_DIR}/List/headers
                            ${CMAKE_SOURCE_DIR}/LinearDS/headers)

# Register tests
include(GoogleTest)
gtest_discover_tests(Tests)
