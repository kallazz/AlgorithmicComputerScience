#ifndef SELECT_KTH_SMALLEST_HPP
#define SELECT_KTH_SMALLEST_HPP

#include <vector>

int partition(std::vector<int> &vec, int left, int right, int pivot, int &comparisons, int &swaps);
int findMedian(std::vector<int> &vec, int left, int right);
int select(std::vector<int> &vec, int left, int right, int i, int &comparisons, int &swaps);

#endif // SELECT_KTH_SMALLEST_HPP 