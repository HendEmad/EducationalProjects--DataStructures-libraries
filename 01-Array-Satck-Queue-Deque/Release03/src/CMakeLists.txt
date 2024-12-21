# Define a static library called ArrayLib from all source files in src
add_library(ArrayLib STATIC Array.cpp Stack.cpp Queue.cpp Deque.cpp)

# Add executable for the main application
add_executable(project_executable main.cpp)

# Link the ArrayLib library with the main executable
target_link_libraries(project_executable PRIVATE ArrayLib)

# Ensure that headers in src are available to targets that link ArrayLib
target_include_directories(ArrayLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
