#ifndef RANDOMIZED_SELECT_HPP
#define RANDOMIZED_SELECT_HPP

#include <vector>

int partition(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps);
int randomizedPartition(std::vector<int> &vec, int left, int right, int &comparisons, int &swaps);
int randomizedSelect(std::vector<int> &vec, int left, int right, int i, int &comparisons, int &swaps);

#endif // RANDOMIZED_SELECT_HPP
