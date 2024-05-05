#include "randomVectorGenerator.hpp"
#include "utils.hpp"

#include <algorithm>
#include <random>

std::mt19937 generator(std::random_device{}());

std::vector<int> generateRandomVector(const int vectorSize) {
    std::uniform_int_distribution<int> dist(0, 2 * vectorSize - 1);
    std::vector<int> randomVector(vectorSize);

    for (int i = 0; i < vectorSize; i++) {
        randomVector[i] = dist(generator);
    }

    return randomVector;
}

std::vector<int> generateRandomAscendingVector(const int vectorSize) {
    std::vector<int> randomVector = generateRandomVector(vectorSize);
    std::sort(randomVector.begin(), randomVector.end());
    return randomVector;
}

std::vector<int> generateRandomDescendingVector(const int vectorSize) {
    std::vector<int> randomVector = generateRandomVector(vectorSize);
    std::sort(randomVector.begin(), randomVector.end(), std::greater<int>());
    return randomVector;
}

