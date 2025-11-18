#include "lzw.hpp"
#include <unordered_map>
#include <string>

std::vector<uint64_t> lzwEncode(const std::vector<unsigned char>& inputData) {
    std::unordered_map<std::string, uint64_t> dictionary;

    // Initialize dictionary with single-byte strings
    for (int i = 0; i < 256; i++) {
        dictionary[std::string(1, (char)i)] = i;
    }

    uint64_t nextCode = 256;
    std::string currentString;
    std::vector<uint64_t> output;

    for (unsigned char byte : inputData) {
        std::string extendedString = currentString + (char)byte;

        if (dictionary.count(extendedString)) {
            currentString = extendedString;
        } else {
            output.push_back(dictionary[currentString]);
            dictionary[extendedString] = nextCode++;
            currentString = std::string(1, (char)byte);
        }
    }

    if (!currentString.empty()) {
        output.push_back(dictionary[currentString]);
    }

    return output;
}

std::vector<unsigned char> lzwDecode(const std::vector<uint64_t>& codes) {
    if (codes.empty()) {
        return {};
    }

    std::vector<std::string> dictionary(256);

    // Initialize dictionary with single-byte strings
    for (int i = 0; i < 256; i++) {
        dictionary[i] = std::string(1, (char)i);
    }

    std::string previousString = dictionary[codes[0]];
    std::string result = previousString;

    for (size_t i = 1; i < codes.size(); i++) {
        uint64_t code = codes[i];
        std::string currentString;

        if (code < dictionary.size()) {
            currentString = dictionary[code];
        } else {
            currentString = previousString + previousString[0];
        }

        result += currentString;
        dictionary.push_back(previousString + currentString[0]);
        previousString = currentString;
    }

    return std::vector<unsigned char>(result.begin(), result.end());
}
