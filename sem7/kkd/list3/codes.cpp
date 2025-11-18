#include "codes.hpp"
#include <bitset>
#include <stdexcept>
#include <algorithm>

std::vector<uint64_t> fibonacciSequence = {1, 2};

std::string convertToBinary(uint64_t number) {
    std::string binary = std::bitset<64>(number).to_string();
    return binary.substr(binary.find('1'));
}

void initializeFibonacciSequence() {
    while (true) {
        size_t lastIndex = fibonacciSequence.size() - 1;
        uint64_t nextValue = fibonacciSequence[lastIndex] + fibonacciSequence[lastIndex - 1];

        // Check for overflow
        if (nextValue < fibonacciSequence[lastIndex]) {
            break;
        }

        fibonacciSequence.push_back(nextValue);
    }
}

std::string eliasOmegaEncode(uint64_t number) {
    if (number == 0) {
        throw std::runtime_error("Elias omega expects number >= 1");
    }

    std::string code = "0";
    uint64_t current = number;

    while (current > 1) {
        std::string binary = convertToBinary(current);
        code = binary + code;
        current = binary.size() - 1;
    }

    return code;
}

std::string eliasGammaEncode(uint64_t number) {
    if (number == 0) {
        throw std::runtime_error("Gamma expects number >= 1");
    }

    std::string binary = convertToBinary(number);
    std::string leadingZeros(binary.size() - 1, '0');

    return leadingZeros + binary;
}

std::string eliasDeltaEncode(uint64_t number) {
    if (number == 0) {
        throw std::runtime_error("Delta expects number >= 1");
    }

    std::string binary = convertToBinary(number);
    std::string gammaLength = eliasGammaEncode(binary.size());

    return gammaLength + binary.substr(1);
}

std::string fibonacciEncode(uint64_t number) {
    if (number == 0) {
        throw std::runtime_error("Fibonacci expects number >= 1");
    }

    std::string code;
    uint64_t remaining = number;
    int index = fibonacciSequence.size() - 1;

    // Find the largest Fibonacci number <= number
    while (fibonacciSequence[index] > remaining) {
        index--;
    }

    // Build the Fibonacci representation
    for (; index >= 0; index--) {
        if (fibonacciSequence[index] <= remaining) {
            code += '1';
            remaining -= fibonacciSequence[index];
        } else {
            code += '0';
        }
    }

    std::reverse(code.begin(), code.end());
    return code + "1";  // Add terminating '1'
}

uint64_t eliasOmegaDecode(const std::string& bitString, size_t& position) {
    uint64_t value = 1;

    while (position < bitString.size() && bitString[position] == '1') {
        size_t length = value;
        value = 0;

        for (size_t i = 0; i <= length && position < bitString.size(); i++) {
            value = (value << 1) | (bitString[position] == '1');
            position++;
        }
    }

    if (position < bitString.size()) {
        position++;  // Skip final '0'
    }

    return value;
}

uint64_t eliasGammaDecode(const std::string& bitString, size_t& position) {
    size_t zeroCount = 0;

    while (position < bitString.size() && bitString[position] == '0') {
        zeroCount++;
        position++;
    }

    uint64_t value = 0;
    for (size_t i = 0; i <= zeroCount && position < bitString.size(); i++) {
        value = (value << 1) | (bitString[position] == '1');
        position++;
    }

    return value;
}

uint64_t eliasDeltaDecode(const std::string& bitString, size_t& position) {
    uint64_t length = eliasGammaDecode(bitString, position);
    uint64_t value = 1;

    for (size_t i = 1; i < length && position < bitString.size(); i++) {
        value = (value << 1) | (bitString[position] == '1');
        position++;
    }

    return value;
}

uint64_t fibonacciDecode(const std::string& bitString, size_t& position) {
    std::string code;

    // Read until we find two consecutive '1's
    while (position < bitString.size()) {
        code += bitString[position++];

        if (code.size() >= 2 && code[code.size() - 1] == '1' && code[code.size() - 2] == '1') {
            break;
        }
    }

    // Convert Fibonacci code to number
    uint64_t value = 0;
    for (size_t i = 0; i < code.size() - 1 && i < fibonacciSequence.size(); i++) {
        if (code[i] == '1') {
            value += fibonacciSequence[i];
        }
    }

    return value;
}
