#include "binarySearch.hpp"


int binarySearch(const std::vector<int> &vec, int left, int right, int v, int &comparisons) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        comparisons++;
        if (vec[mid] == v) {
            return 1;
        }

        comparisons++;
        if (vec[mid] < v) {
            return binarySearch(vec, mid + 1, right, v, comparisons);
        }
        return binarySearch(vec, left, mid - 1, v, comparisons);
    }
    return 0;
}