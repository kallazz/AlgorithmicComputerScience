#include "randomizedSelect.hpp"
#include "select.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

int main() {
    const std::vector<int> vec = {3, 2, 2, 1};
    const std::vector<int> expectedResults = {1, 2, 2, 3};
    for (int i = 0; i < vec.size(); i++) {
        std::vector<int> vecCopy = vec;
        assert(randomizedSelect(vecCopy, 0, vec.size() - 1, i + 1) == expectedResults[i]);
    }
    std::cout << "All tests passed!\n";
}
