#include "kmp.hpp"

#include <iostream>
#include <vector>

std::vector<int> computePrefixFunction(const std::string &pattern) {
    const int patternLength = pattern.length();
    std::vector<int> prefixVector(patternLength);
    prefixVector[0] = 0;
    int k = 0;

    for (int q = 1; q < patternLength; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = prefixVector[k - 1];
        }

        if (pattern[k] == pattern[q]) {
            k++;
        }

        prefixVector[q] = k;
    }

    return prefixVector;
}

std::vector<int> kmpMatcher(const std::string &text, const std::string &pattern) {
    const int textLength = text.length();
    const int patternLength = pattern.length();
    if (patternLength == 0 || patternLength > textLength) {
        return {};
    }

    std::vector<int> matches;
    const auto prefixVector = computePrefixFunction(pattern);
    int matchedChars = 0;

    for (int i = 0; i < textLength; i++) {
        while (matchedChars > 0 && pattern[matchedChars] != text[i]) {
            matchedChars = prefixVector[matchedChars - 1];
        }

        if (pattern[matchedChars] == text[i]) {
            matchedChars++;
        }

        if (matchedChars == patternLength) {
            matches.push_back(i - patternLength + 1);
            matchedChars = prefixVector[matchedChars - 1];
        }
    }

    return matches;
}