#include "randomizedSelect.hpp"

#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    if (argc < 4) {
        std::cerr << "Expected at least 3 arguments! Got " << argc << '\n';
        return 1;
    }

    const int vectorSize = std::stoi(argv[1]);
    const int statisticOrder = std::stoi(argv[2]);
    std::vector<int> inputVector;
    for (int i = 3; i < argc; i++) {
        inputVector.push_back(std::stoi(argv[i]));
    }

    int comparisons = 0;
    int swaps = 0;

    randomizedSelect(inputVector, 0, inputVector.size() - 1, statisticOrder, comparisons, swaps);

    std::cout << "Comparisons: " << comparisons << "\n";
    std::cout << "Swaps: " << swaps << "\n";

    return 0;
}
