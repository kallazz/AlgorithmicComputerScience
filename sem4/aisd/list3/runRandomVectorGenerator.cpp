#include "randomVectorGenerator.hpp"
#include "utils.hpp"

#include <iostream>
#include <random>

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

    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, vectorSize);
    const int randomOrderStatistic = dist(generator);

    switch (generatorType) {
        case GeneratorOption::Random:
            std::cout << vectorSize << " " << randomOrderStatistic  << " ";
            printVector(generateRandomVector(vectorSize));
            std::cout << '\n';
            break;
        case GeneratorOption::Ascending:
            std::cout << vectorSize << " " << randomOrderStatistic << " ";
            printVector(generateRandomAscendingVector(vectorSize));
            std::cout << '\n';
            break;
        case GeneratorOption::Descending:
            std::cout << vectorSize << " " << randomOrderStatistic << " ";
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