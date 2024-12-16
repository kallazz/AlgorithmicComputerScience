#include "enums.hpp"

#include <unordered_map>

const std::unordered_map<std::string, AlgorithmType> STRING_TO_ALGORITHM = {
    {"dijkstra", DIJKSTRA},
    {"dial", DIAL},
    {"radixheap", RADIXHEAP}
};

AlgorithmType getAlgorithmFromString(const std::string& str) {
    return STRING_TO_ALGORITHM.at(str);
}
