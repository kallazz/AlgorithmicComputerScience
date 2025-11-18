#ifndef CODES_HPP
#define CODES_HPP

#include <string>
#include <cstdint>
#include <vector>

std::string convertToBinary(uint64_t number);

std::string eliasOmegaEncode(uint64_t number);
std::string eliasGammaEncode(uint64_t number);
std::string eliasDeltaEncode(uint64_t number);
std::string fibonacciEncode(uint64_t number);

uint64_t eliasOmegaDecode(const std::string& bitString, size_t& position);
uint64_t eliasGammaDecode(const std::string& bitString, size_t& position);
uint64_t eliasDeltaDecode(const std::string& bitString, size_t& position);
uint64_t fibonacciDecode(const std::string& bitString, size_t& position);

void initializeFibonacciSequence();
extern std::vector<uint64_t> fibonacciSequence;

#endif  // CODES_HPP
