#include "utils.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

std::mt19937 generator(std::random_device{}());

std::vector<int> generateRandomVector(const int vectorSize) {
    std::uniform_int_distribution<int> dist(0, 2 * vectorSize - 1);
    std::vector<int> randomVector(vectorSize);

    for (int i = 0; i < vectorSize; i++) {
        int randomNumber = dist(generator);
        while (!randomVector.empty() && std::find(randomVector.begin(), randomVector.end(), randomNumber) != randomVector.end()) {
            randomNumber = dist(generator);
        }
        randomVector[i] = randomNumber;
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

enum GeneratorOption {
    Invalid,
    Random,
    Ascending,
    Descending 
};

GeneratorOption resolveOption(const std::string &input) {
    if (input == "random") return GeneratorOption::Random;
    if (input == "ascending") return GeneratorOption::Ascending;
    if (input == "descending") return GeneratorOption::Descending;
    return GeneratorOption::Invalid;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <generator_type> <vector_size>\n";
        return 1;
    }

    const GeneratorOption generatorType = resolveOption(argv[1]);
    const int vectorSize = std::stoi(argv[2]);

    switch (generatorType) {
        case GeneratorOption::Random:
            std::cout << vectorSize << " " << static_cast<int>(vectorSize /  2) << " ";
            printVector(generateRandomVector(vectorSize));
            std::cout << '\n';
            break;
        case GeneratorOption::Ascending:
            std::cout << vectorSize << " " << static_cast<int>(vectorSize /  2) << " ";
            printVector(generateRandomAscendingVector(vectorSize));
            std::cout << '\n';
            break;
        case GeneratorOption::Descending:
            std::cout << vectorSize << " " << static_cast<int>(vectorSize /  2) << " ";
            printVector(generateRandomDescendingVector(vectorSize));
            std::cout << '\n';
            break;
        default:
            std::cerr << "Invalid generator type!\n";
            return 1;
            break;
    }

    return 0;
}
