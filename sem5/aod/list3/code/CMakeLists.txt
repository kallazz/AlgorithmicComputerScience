cmake_minimum_required(VERSION 3.10)
project(List3)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(RunTests src/testDijkstraAlgorithms.cpp src/DijkstraAlgorithms.cpp src/Graph.cpp)
add_executable(RunAlgorithm src/runAlgorithm.cpp src/DijkstraAlgorithms.cpp src/Graph.cpp src/CommandLineParser.cpp src/AlgorithmRunner.cpp src/enums.cpp)
add_executable(RunExperiment src/runExperiment.cpp src/DijkstraAlgorithms.cpp src/Graph.cpp src/CommandLineParser.cpp src/AlgorithmRunner.cpp src/enums.cpp)
