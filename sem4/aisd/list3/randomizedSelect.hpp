#ifndef RANDOMIZED_SELECT_HPP
#define RANDOMIZED_SELECT_HPP

#include <vector>

int partition(std::vector<int> &vec, int low, int high);
int randomizedPartition(std::vector<int> &vec, int low, int high);
int randomizedSelect(std::vector<int> &vec, int low, int high, int i);

#endif // RANDOMIZED_SELECT_HPP
