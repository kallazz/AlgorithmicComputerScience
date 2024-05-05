#include "randomizedSelect.hpp"
#include "select.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

int main() {
    const std::vector<int> vec = {2, 7, 12, 8, 3, 2, 4, 4, 4, 1, 12, 10};
    const std::vector<int> expectedResults = {1, 2, 2, 3, 4, 4, 4, 7, 8, 10, 12, 12};
    int comparisons, swaps;
    for (int i = 0; i < vec.size(); i++) {
        std::vector<int> vecCopy = vec;
        assert(randomizedSelect(vecCopy, 0, vec.size() - 1, i + 1, comparisons, swaps) == expectedResults[i]);
    }
    std::cout << "Randomized Select Tests Passed!\n";

    for (int i = 0; i < vec.size(); i++) {
        std::vector<int> vecCopy = vec;
        assert(select(vecCopy, 0, vec.size() - 1, i + 1, comparisons, swaps) == expectedResults[i]);
    }
    std::cout << "Select Tests Passed!\n";
}
