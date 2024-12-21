# files
set(LINEARDS_HEADERS Headers/Stack.h Headers/Queue.h Headers/Deque.h)
set(LINEARDS_SOURCES Src/Stack.cpp Src/Queue.cpp Src/Deque.cpp)

# Library
add_library(LinearDS ${LINEARDS_HEADERS} ${LINEARDS_SOURCES})

# Main executable
add_executable(lineards_main main.cpp)
target_include_directories(LinearDS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers)
target_link_libraries(lineards_main LinearDS)

# Tests
add_executable(lineards_tests test/test_lineards.cpp)
target_link_libraries(lineards_tests PRIVATE LinearDS gtest gtest_main)
add_test(NAME LinearDSTests COMMAND lineards_tests)
