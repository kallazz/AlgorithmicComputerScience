cmake_minimum_required(VERSION 3.10)
project(List1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Presentation1 src/presentations/presentTask1.cpp src/Graph.cpp src/graphAlgorithms.cpp)
add_executable(Presentation2 src/presentations/presentTask2.cpp src/Graph.cpp src/graphAlgorithms.cpp src/graphHelpers.cpp)
add_executable(Presentation3 src/presentations/presentTask3.cpp src/Graph.cpp src/graphAlgorithms.cpp src/graphHelpers.cpp)
add_executable(Presentation4 src/presentations/presentTask4.cpp src/Graph.cpp src/graphAlgorithms.cpp src/graphHelpers.cpp)
