#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>

enum AlgorithmType {
    DIJKSTRA,
    DIAL,
    RADIXHEAP
};

enum ExperimentType {
    SOURCES,
    PAIRS
};

AlgorithmType getAlgorithmFromString(const std::string& str);

#endif // ENUMS_HPP
