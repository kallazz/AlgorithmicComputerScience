#include "randomVectorGenerator.hpp"
#include "utils.hpp"

#include <iostream>

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