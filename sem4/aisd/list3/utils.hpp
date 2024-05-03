#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

constexpr int MAX_VECTOR_PRINT_SIZE = 50;

void printVector(const std::vector<int> &vec);
void printInfo(const std::string &text, const std::vector<int> &vec);

#endif // UTILS_HPP