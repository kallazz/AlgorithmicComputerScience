#include "fa.hpp"

#include <unordered_set>

std::unordered_set<char> computeAlphabet(const std::string &text) {
    std::unordered_set<char> alphabet;

    for (const auto letter : text) {
        alphabet.insert(letter);
    }

    return alphabet;
}

TransitionFunction computeTransitionFunction(const std::string &pattern, const std::unordered_set<char> &alphabet) {
    TransitionFunction transitionFunction;
    const int patternLength = pattern.length();

    for (int state = 0; state <= patternLength; state++) {
        for (const auto letter : alphabet) {
            int k = std::min(patternLength, state + 1);

            while (!(pattern.substr(0, state) + letter).ends_with(pattern.substr(0, k))) {
                k--;
            }

            transitionFunction[{state, letter}] = k;
        }
    }

    return transitionFunction;
}

std::vector<int> finiteAutomationMatcher(const std::string &text, const TransitionFunction &transitionFunction,
                                         const int patternLength) {
    const int textLength = text.length();
    if (patternLength == 0 || patternLength > textLength) {
        return {};
    }

    std::vector<int> matches;
    int state = 0;

    for (int i = 0; i < textLength; i++) {
        state = transitionFunction.at({state, text[i]});

        if (state == patternLength) {
            matches.push_back(i - patternLength + 1);
        }
    }

    return matches;
}
