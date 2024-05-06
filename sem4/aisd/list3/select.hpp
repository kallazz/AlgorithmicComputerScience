#ifndef SELECT_HPP
#define SELECT_HPP

#include <vector>

int quickSortPartition(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps);
void quickSort(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps);
int partition(std::vector<int> &vec, int left, int right, int pivot, int &comparisons, int &swaps);
int findMedian(std::vector<int> &vec, int left, int right);
int select(std::vector<int> &vec, int left, int right, int i, int &comparisons, int &swaps, int mediansArraySize = 5);

#endif // SELECT_HPP
