#include "utils.hpp"
#include "randomizedSelect.hpp"

#include <random>

int partition(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps) {
    int pivot = vec[right];
    int i = left;
    for (int j = left; j <= right - 1; j++) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            swaps++;
            i += 1;
        }
        comparisons++;
    }

    std::swap(vec[i], vec[right]);
    swaps++;
    // printInfo("After partition:", vec);
    return i;
}

int randomizedPartition(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps) {
    int n = right - left + 1;
    int randomPivot = rand() % n;
    std::swap(vec[left + randomPivot], vec[right]);
    swaps++;
    return partition(vec, left, right, comparisons, swaps);
}

int randomizedSelect(std::vector<int> &vec, int left, int right, int i, int &comparisons, int &swaps) {
    if (left == right) return vec[left];
    int globalPivotIndex = randomizedPartition(vec, left, right, comparisons, swaps);
    int localPivotIndex = globalPivotIndex - left + 1;
    if (i == localPivotIndex) {
       return vec[globalPivotIndex];
    } else if (localPivotIndex > i) {
        return randomizedSelect(vec, left, globalPivotIndex - 1, i, comparisons, swaps);
    } else {
        return randomizedSelect(vec, globalPivotIndex + 1, right, i - localPivotIndex, comparisons, swaps);
    }
}
