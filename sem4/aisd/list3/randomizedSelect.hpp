#ifndef RANDOMIZED_SELECT_HPP
#define RANDOMIZED_SELECT_HPP

#include <vector>

int partition(std::vector<int> &vec, int left, int right);
int randomizedPartition(std::vector<int> &vec, int left, int right);
int randomizedSelect(std::vector<int> &vec, int left, int right, int i);

#endif // RANDOMIZED_SELECT_HPP
