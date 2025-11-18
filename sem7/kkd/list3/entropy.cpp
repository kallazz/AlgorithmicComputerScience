#include "entropy.hpp"
#include <unordered_map>
#include <cmath>

double calculateInputEntropy(const std::vector<unsigned char>& data) {
    std::unordered_map<unsigned char, size_t> frequency;

    for (auto byte : data) {
        ++frequency[byte];
    }

    double entropy = 0.0;
    size_t totalBytes = data.size();

    if (totalBytes > 0) {
        for (const auto& pair : frequency) {
            double probability = static_cast<double>(pair.second) / totalBytes;
            entropy -= probability * std::log2(probability);
        }
    }

    return entropy;
}

double calculateCodeEntropy(const std::string& bitString) {
    size_t onesCount = 0;

    for (char bit : bitString) {
        if (bit == '1') {
            ++onesCount;
        }
    }

    size_t zerosCount = bitString.size() - onesCount;
    double entropy = 0.0;
    size_t totalBits = bitString.size();

    if (totalBits > 0) {
        double probabilityZero = static_cast<double>(zerosCount) / totalBits;
        double probabilityOne = static_cast<double>(onesCount) / totalBits;

        if (probabilityZero > 0) {
            entropy -= probabilityZero * std::log2(probabilityZero);
        }
        if (probabilityOne > 0) {
            entropy -= probabilityOne * std::log2(probabilityOne);
        }
    }

    return entropy;
}
