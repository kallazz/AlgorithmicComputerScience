#include "utils.hpp"
#include "randomizedSelect.hpp"

#include <random>

int partition(std::vector<int> &vec, int left, int right) {
    int pivot = vec[right];
    int i = left;
    for (int j = left; j <= right - 1; j++) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            i += 1;
        }
    }

    std::swap(vec[i], vec[right]);
    printInfo("After partition:", vec);
    return i;
}

int randomizedPartition(std::vector<int> &vec, int left, int right) {
    int n = right - left + 1;
    int randomPivot = rand() % n;
    std::swap(vec[left + randomPivot], vec[right]);
    return partition(vec, left, right);
}

int randomizedSelect(std::vector<int> &vec, int left, int right, int i) {
    if (left == right) return vec[left];
    int globalPivotIndex = randomizedPartition(vec, left, right);
    int localPivotIndex = globalPivotIndex - left + 1;
    if (i == localPivotIndex) {
       return vec[globalPivotIndex];
    } else if (localPivotIndex > i) {
        return randomizedSelect(vec, left, globalPivotIndex - 1, i);
    } else {
        return randomizedSelect(vec, globalPivotIndex + 1, right, i - localPivotIndex);
    }
}
