## Folders and Files
* `src/`: Contains the source code files.
* `tests/`: Contains the unit test files using Google Test.
* `Release 3/ CMakeLists.txt`: The main CMake configuration file.
* `tests/CMakeLists.txt`: CMake Configuration for building tests and importing the Google Test lib.

## Structure:
```cpp
Release 3/
├── CMakeLists.txt
├── src/
│   ├── Array.h
│   ├── Array.cpp
│   ├── Stack.h
│   ├── Stack.cpp
│   ├── Queue.h
│   ├── Queue.cpp
│   ├── Deque.h
│   ├── Deque.cpp
│   └── main.cpp
└── tests/
    ├── CMakeLists.txt
    ├── Array_test.cpp
    ├── Stack_test.cpp
    ├── Queue_test.cpp
    └── Deque_test.cpp
```