#include "utils.hpp"
#include "select.hpp"

#include <algorithm>
#include <vector>

int findMedian(std::vector<int> &vec, int left, int right) {
    std::sort(vec.begin() + left, vec.begin() + right + 1);
    return vec[left + (right - left) / 2];
}

int partition(std::vector<int> &vec, int left, int right, int pivot) {
    int i;
    for (i = left; i < right; i++) {
        if (vec[i] == pivot) {
            break;
        }
    }
    std::swap(vec[i], vec[right]);

    i = left;
    for (int j = left; j <= right - 1; j++) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            i += 1;
        }
    }

    std::swap(vec[i], vec[right]);
    printInfo("After partition: ", vec);
    return i;
}

int select(std::vector<int> &vec, int left, int right, int k) {
    int n = right - left + 1;
    std::vector<int> medians((n + 4) / 5);
    int i = 0;
    while (i < n / 5) {
        medians[i] = findMedian(vec, left + i * 5, left + i * 5 + 4); 
        i += 1;
    }
    if (i * 5 < n) {
        medians[i] = findMedian(vec, left + i * 5, left + i * 5 + (n % 5 - 1));
        i += 1;
    }

    int medianOfMedians = (i == 1) ? medians[0] : select(medians, 0, i - 1, i / 2);

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
