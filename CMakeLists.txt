cmake_minimum_required(VERSION 4.3)
project(dubLlist)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dubLlist
        main.cpp
        DLList.cpp
        DLList.h)

enable_testing()

add_executable(DLListTests
        tests/DLListTests.cpp)

target_include_directories(DLListTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_test(NAME DLListTests
        COMMAND DLListTests --reporter compact)
