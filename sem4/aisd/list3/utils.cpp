#include "utils.hpp"

#include <iostream>
#include <vector>

void printVector(const std::vector<int> &vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << vec[vec.size() - 1];
}

void printVectorWithCommas(const std::vector<int> &vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size() - 1];
}

void printInfo(const std::string &text, const std::vector<int> &vec) {
    if (vec.size() < MAX_VECTOR_PRINT_SIZE) {
        std::cout << text;
        printVectorWithCommas(vec);
        std::cout << '\n';
    }
}