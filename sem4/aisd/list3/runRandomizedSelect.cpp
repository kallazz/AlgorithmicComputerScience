#include "randomizedSelect.hpp"
#include "utils.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int vectorSize;
    int orderStatistic;
    std::cin >> vectorSize;
    std::cin >> orderStatistic;
    std::vector<int> inputVector(vectorSize);
    for (int i = 0; i < vectorSize; i++) {
        std::cin >> inputVector[i];
    }

    int comparisons = 0;
    int swaps = 0;
    std::vector<int> vectorToModify = inputVector;

    int result = randomizedSelect(vectorToModify, 0, inputVector.size() - 1, orderStatistic, comparisons, swaps);

    std::cout << "\nInitial array: ";
    printVectorWithCommas(inputVector);
    std::cout << "After algorithm: ";
    printVectorWithCommas(vectorToModify);
    std::sort(inputVector.begin(), inputVector.end());
    std::cout << "Sorted: ";
    printVectorWithCommas(inputVector);
    std::cout << "Found " << orderStatistic << "-th order statistic: " << result << '\n';
    std::cout << "Comparisons: " << comparisons << "\n";
    std::cout << "Swaps: " << swaps << "\n";

    return 0;
}
