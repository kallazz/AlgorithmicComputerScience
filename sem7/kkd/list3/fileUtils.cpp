#include "fileUtils.hpp"
#include <fstream>
#include <iterator>
#include <stdexcept>

std::vector<unsigned char> readBinaryFile(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);

    if (!input) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    std::vector<unsigned char> data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    return data;
}

void writeBinaryFile(const std::string& filename, const std::vector<unsigned char>& data) {
    std::ofstream output(filename, std::ios::binary);

    if (!output) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    output.write((char*)data.data(), data.size());
}

std::string bitStringToBytes(const std::string& bitString, uint8_t& paddingBits) {
    paddingBits = (8 - (bitString.size() % 8)) % 8;
    std::string result;

    uint8_t currentByte = 0;
    int bitCount = 0;

    for (char bit : bitString) {
        currentByte = (currentByte << 1) | (bit == '1');
        bitCount++;

        if (bitCount == 8) {
            result += currentByte;
            currentByte = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0) {
        currentByte <<= (8 - bitCount);
        result += currentByte;
    }

    return result;
}

std::string bytesToBitString(const std::vector<unsigned char>& bytes, uint8_t paddingBits) {
    std::string bitString;

    for (unsigned char byte : bytes) {
        for (int i = 7; i >= 0; i--) {
            bitString += ((byte >> i) & 1) ? '1' : '0';
        }
    }

    // Remove padding from last byte
    if (!bitString.empty() && paddingBits > 0) {
        bitString = bitString.substr(0, bitString.size() - paddingBits);
    }

    return bitString;
}
