#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP

#include <string>
#include <cstdint>

uint8_t getCodeTypeId(const std::string& codeType);
std::string getCodeTypeName(uint8_t codeTypeId);
std::string encodeValue(uint64_t value, const std::string& codeType);
uint64_t decodeValue(const std::string& bitString, size_t& position, const std::string& codeType);
void encodeFile(const std::string& inputFile, const std::string& outputFile, const std::string& codeType);
void decodeFile(const std::string& inputFile, const std::string& outputFile, const std::string& codeType);

#endif  // COMPRESSION_HPP
