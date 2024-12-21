# Files
set(LIST_HEADERS headers/ForwardList.h headers/DoublyList.h headers/CircularList.h headers/Ilist.h)
set(LIST_SOURCES src/ForwardList.cpp src/DoublyList.cpp src/CircularList.cpp)

# Library
add_library(List ${LIST_HEADERS} ${LIST_SOURCES})

# Main executable
add_executable(list_main list_main.cpp)
target_include_directories(List PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_link_libraries(list_main List)

# Tests
add_executable(list_tests test/test_list.cpp)
target_link_libraries(list_tests PRIVATE List gtest gtest_main)
add_test(NAME ListTests COMMAND list_tests)
