#include "randomizedSelect.hpp"
#include "select.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

int main() {
    const std::vector<int> vec = {7, 8, 3, 2, 4, 1};
    const std::vector<int> expectedResults = {1, 2, 3, 4, 7, 8};
    for (int i = 0; i < vec.size(); i++) {
        std::vector<int> vecCopy = vec;
        std::vector<int> vecCopy2 = vec;
        int result = select(vecCopy2, 0, vec.size() - 1, i + 1);
        std::cout << "The result is " << result << '\n';
        assert(result == expectedResults[i]);
    }
    std::cout << "Randomized Select Tests Passed!\n";

    for (int i = 0; i < vec.size(); i++) {
        std::vector<int> vecCopy = vec;
        assert(select(vecCopy, 0, vec.size() - 1, i + 1) == expectedResults[i]);
    }
    std::cout << "Select Tests Passed!\n";
}
