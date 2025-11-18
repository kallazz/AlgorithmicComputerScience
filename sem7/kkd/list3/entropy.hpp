#ifndef ENTROPY_HPP
#define ENTROPY_HPP

#include <vector>
#include <string>

double calculateInputEntropy(const std::vector<unsigned char>& data);
double calculateCodeEntropy(const std::string& bitString);

#endif  // ENTROPY_HPP
