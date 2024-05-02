#include "randomizedSelect.hpp"

#include <random>
#include <vector>


int partition(std::vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (vec[j] < pivot) {
            i += 1;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

int randomizedPartition(std::vector<int> &vec, int low, int high) {
    int randomIndex = rand() % high + 1; 
    std::swap(vec[randomIndex], vec[high]);
    return partition(vec, low, high);
}

int randomizedSelect(std::vector<int> &vec, int low, int high, int i) {
    if (low == high) return vec[low];
    int pivot = randomizedPartition(vec, low, high);
    int k = pivot - low + 1;
    if (i == k) {
       return vec[pivot];
    }
    else if (i < k) {
        return randomizedSelect(vec, low, pivot - 1, i);
    }
    else {
        return randomizedSelect(vec, pivot + 1, high, i - k);
    }
}
