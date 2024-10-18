cmake_minimum_required(VERSION 3.10)
project(List1)

set(CMAKE_CXX_STANDARD 20)

set(ALGORITHMS
    algorithms/fa.cpp
    algorithms/kmp.cpp
)

add_executable(Tests tests.cpp ${ALGORITHMS})
add_executable(FA faRunner.cpp ${ALGORITHMS})
add_executable(KMP kmpRunner.cpp ${ALGORITHMS})
