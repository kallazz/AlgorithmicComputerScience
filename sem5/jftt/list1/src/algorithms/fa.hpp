#ifndef FA_HPP
#define FA_HPP

#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct PairHash {
    template <class T1, class T2> std::size_t operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

using TransitionFunction = std::unordered_map<std::pair<int, char>, int, PairHash>;

std::unordered_set<char> computeAlphabet(const std::string &text);
TransitionFunction computeTransitionFunction(const std::string &pattern, const std::unordered_set<char> &alphabet);
std::vector<int> finiteAutomationMatcher(const std::string &text, const TransitionFunction &transitionFunction,
                                         const int patternLength);

#endif // FA_HPP