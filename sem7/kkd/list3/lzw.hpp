#ifndef LZW_HPP
#define LZW_HPP

#include <vector>
#include <cstdint>

std::vector<uint64_t> lzwEncode(const std::vector<unsigned char>& inputData);
std::vector<unsigned char> lzwDecode(const std::vector<uint64_t>& codes);

#endif  // LZW_HPP
