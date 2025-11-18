#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>
#include <vector>
#include <cstdint>

std::vector<unsigned char> readBinaryFile(const std::string& filename);
void writeBinaryFile(const std::string& filename, const std::vector<unsigned char>& data);
std::string bitStringToBytes(const std::string& bitString, uint8_t& paddingBits);
std::string bytesToBitString(const std::vector<unsigned char>& bytes, uint8_t paddingBits);

#endif  // FILE_UTILS_HPP
