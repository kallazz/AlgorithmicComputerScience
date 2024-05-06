#include "utils.hpp"
#include "select.hpp"

#include <algorithm>
#include <vector>

int quickSortPartition(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps) {
    int pivot = vec[right];
    int i = left;
    for (int j = left; j <= right - 1; j++) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            i += 1;
        }
        comparisons++;
        swaps++;
    }

    std::swap(vec[i], vec[right]);
    swaps++;
    return i;
}

void quickSort(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps) {
    if (left >= right) {
        return;
    }

    int pivotIndex = quickSortPartition(vec, left, right, comparisons, swaps);
    quickSort(vec, left, pivotIndex - 1, comparisons, swaps);
    quickSort(vec, pivotIndex + 1, right, comparisons, swaps);
}

int findMedian(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps) {
    quickSort(vec, left, right, comparisons, swaps);
    return vec[left + (right - left) / 2];
}

int partition(std::vector<int> &vec, int left, int right, int pivot, int &comparisons, int &swaps) {
    int i;
    for (i = left; i < right; i++) {
        comparisons++;
        if (vec[i] == pivot) {
            break;
        }
    }
    std::swap(vec[i], vec[right]);
    swaps++;

    i = left;
    for (int j = left; j <= right - 1; j++) {
        comparisons++;
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            swaps++;
            i += 1;
        }
    }

    std::swap(vec[i], vec[right]);
    swaps++;
    return i;
}

int select(std::vector<int> &vec, int left, int right, int k, int &comparisons, int &swaps, int mediansArraySize) {
    printInfo("Array after entering function: ", vec);
    int n = right - left + 1;
    std::vector<int> medians((n + mediansArraySize - 1) / mediansArraySize);
    int i = 0;
    while (i < n / mediansArraySize) {
        medians[i] = findMedian(vec, left + i * mediansArraySize, left + i * mediansArraySize + mediansArraySize - 1, comparisons, swaps); 
        i += 1;
    }
    if (i * mediansArraySize < n) {
        medians[i] = findMedian(vec, left + i * mediansArraySize, left + i * mediansArraySize + (n % mediansArraySize - 1), comparisons, swaps);
        i += 1;
    }

    int medianOfMedians = (i == 1) ? medians[0] : select(medians, 0, i - 1, i / 2, comparisons, swaps, mediansArraySize);

    int pivotIndex = partition(vec, left, right, medianOfMedians, comparisons, swaps);
    i = pivotIndex - left + 1;
    if (i == k) {
        return vec[pivotIndex]; 
    } else if (i > k) {
        return select(vec, left, pivotIndex - 1, k, comparisons, swaps, mediansArraySize);
    } else {
        return select(vec, pivotIndex + 1, right, k - i, comparisons, swaps, mediansArraySize);
    }
}
