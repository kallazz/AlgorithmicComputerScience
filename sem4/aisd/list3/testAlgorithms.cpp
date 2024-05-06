// g++ testAlgorithms.cpp binarySearch.cpp randomizedSelect.cpp select.cpp
#include "binarySearch.hpp"
#include "randomizedSelect.hpp"
#include "select.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

void testSelectionAlgorithms() {
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
}

void testBinarySearch() {
    const std::vector<int> vec = {1, 3, 4, 5, 7, 10};
    int comparisons;
    assert(binarySearch(vec, 0, vec.size() - 1, 0, comparisons) == 0);
    assert(binarySearch(vec, 0, vec.size() - 1, 1, comparisons) == 1);
    assert(binarySearch(vec, 0, vec.size() - 1, 2, comparisons) == 0);
    assert(binarySearch(vec, 0, vec.size() - 1, 3, comparisons) == 1);
    assert(binarySearch(vec, 0, vec.size() - 1, 4, comparisons) == 1);
    assert(binarySearch(vec, 0, vec.size() - 1, 5, comparisons) == 1);
    assert(binarySearch(vec, 0, vec.size() - 1, 6, comparisons) == 0);
    assert(binarySearch(vec, 0, vec.size() - 1, 7, comparisons) == 1);
    assert(binarySearch(vec, 0, vec.size() - 1, 8, comparisons) == 0);
    assert(binarySearch(vec, 0, vec.size() - 1, 9, comparisons) == 0);
    assert(binarySearch(vec, 0, vec.size() - 1, 10, comparisons) == 1);
    assert(binarySearch(vec, 0, vec.size() - 1, 11, comparisons) == 0);
}


int main() {
    testSelectionAlgorithms();
    std::cout << "Select Tests Passed!\n";
    testBinarySearch();
    std::cout << "Binary Search Tests Passed!\n";
}
