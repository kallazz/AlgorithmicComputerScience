cmake_minimum_required(VERSION 3.10)
project(List1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tests src/tests.cpp src/algorithms/fa.cpp src/algorithms/kmp.cpp)
add_executable(FA src/faRunner.cpp src/algorithms/fa.cpp)
add_executable(KMP src/kmpRunner.cpp src/algorithms/kmp.cpp)
