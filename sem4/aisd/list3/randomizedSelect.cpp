#include "utils.hpp"
#include "randomizedSelect.hpp"

#include <random>

int partition(std::vector<int> &vec, int left, int right) {
    int pivot = vec[right];
    int i = left - 1;
    for (int j = left; j <= right; j++) {
        if (vec[j] < pivot) {
            i += 1;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[right]);
    const std::string text = "After partition: "; 
    // printInfo(text, vec);
    return i + 1;
}

int randomizedPartition(std::vector<int> &vec, int left, int right) {
    int randomIndex = rand() % right + 1; 
    std::swap(vec[randomIndex], vec[right]);
    return partition(vec, left, right);
}

int randomizedSelect(std::vector<int> &vec, int left, int right, int i) {
    if (left == right) return vec[left];
    int globalPivotIndex = randomizedPartition(vec, left, right);
    int localPivotIndex = globalPivotIndex - left + 1;
    if (i == localPivotIndex) {
       return vec[globalPivotIndex];
    } else if (i < localPivotIndex) {
        return randomizedSelect(vec, left, globalPivotIndex - 1, i);
    } else {
        return randomizedSelect(vec, globalPivotIndex + 1, right, i - localPivotIndex);
    }
}
