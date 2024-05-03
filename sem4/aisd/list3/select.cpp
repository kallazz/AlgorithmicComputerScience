#include "utils.hpp"
#include "select.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

int findMedian(std::vector<int> &vec, int left, int right) {
    std::sort(vec.begin() + left, vec.begin() + right);
    std::cout << left << " " << right << " Vec after sort:";
    printVector(vec);
    return vec[(right - left) / 2];
}

int partition(std::vector<int> &vec, int left, int right, int pivot) {
    int i = left - 1;
    for (int j = left; j <= right; j++) {
        if (vec[j] < pivot) {
            i += 1;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[right]);
    // printInfo("After partition: ", vec);
    return i + 1;
}

int select(std::vector<int> &vec, int left, int right, int k) {
    int n = right - left + 1;
    std::vector<int> medians((n + 4) / 5);
    int i = 0;
    while (i < n / 5) {
        medians[i] = findMedian(vec, i * 5, i * 5 + 4); 
        i += 1;
    }
    if (i * 5 < n) {
        medians[i] = findMedian(vec, i * 5, n - 1);
        i += 1;
    }

std::cout << "The medians are" << medians[0] << " " << medians[1] << '\n';
    int medianOfMedians;
    if (i == 1) {
        medianOfMedians = medians[0];
    } else {
        medianOfMedians = select(medians, 0, i - 1, i / 2);
    }

    int pivotIndex = partition(vec, left, right, medianOfMedians);
    i = pivotIndex - left + 1;
    if (i == k) {
        return vec[pivotIndex]; 
    } else if (i > k) {
        return select(vec, left, pivotIndex - 1, k);
    } else {
        return select(vec, pivotIndex + 1, right, k - i);
    }
}
