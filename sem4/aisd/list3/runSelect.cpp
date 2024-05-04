#include "select.hpp"

#include <iostream>
#include <vector>

int main() {
    int vectorSize;
    int statisticOrder; 
    std::cin >> vectorSize;
    std::cin >> statisticOrder;
    std::vector<int> inputVector(vectorSize);
    for (int i = 3; i < vectorSize; i++) {
        std::cin >> inputVector[i];
    }

    int comparisons = 0;
    int swaps = 0;

    select(inputVector, 0, inputVector.size() - 1, statisticOrder, comparisons, swaps);

    std::cout << "Comparisons: " << comparisons << "\n";
    std::cout << "Swaps: " << swaps << "\n";

    return 0;
}
