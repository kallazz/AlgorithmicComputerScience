#include "algorithms/fa.hpp"
#include "algorithms/kmp.hpp"

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

const std::unordered_set<char> ALPHABET = {'a', 'b', 'c', 'd'};

void assertVectorContains(const std::vector<int> &vec, const std::vector<int> &expectedElements) {
    assert(vec.size() == expectedElements.size());
    for (int i = 0; i < vec.size(); i++) {
        assert(vec[i] == expectedElements[i]);
    }
}

std::pair<std::vector<int>, std::vector<int>> createTest(const std::string &text, const std::string &pattern) {
    const TransitionFunction transitionFunction = computeTransitionFunction(pattern, ALPHABET);
    return {finiteAutomationMatcher(text, transitionFunction, pattern.length()), kmpMatcher(text, pattern)};
}

void testEmptyTextEmptyPattern() {
    const auto [faResult, kmpResult] = createTest("", "");
    assert(faResult.empty());
    assert(kmpResult.empty());
}

void testTextWithEmptyPattern() {
    const auto [faResult, kmpResult] = createTest("abcd", "");
    assert(faResult.empty());
    assert(kmpResult.empty());
}

void testEmptyTextWithPattern() {
    const auto [faResult, kmpResult] = createTest("", "ab");
    assert(faResult.empty());
    assert(kmpResult.empty());
}

void testTextWithPattern() {
    const auto [faResult, kmpResult] = createTest("abcd", "ab");
    assertVectorContains(faResult, {0});
    assertVectorContains(kmpResult, {0});
}

void testTextWithRepeatingPattern() {
    const auto [faResult, kmpResult] = createTest("abcabcabc", "ab");
    assertVectorContains(faResult, {0, 3, 6});
    assertVectorContains(kmpResult, {0, 3, 6});
}

void testTextWithNothingButPattern() {
    const auto [faResult, kmpResult] = createTest("aaa", "a");
    assertVectorContains(faResult, {0, 1, 2});
    assertVectorContains(kmpResult, {0, 1, 2});
}

void testTextWithPatternAtTheEnd() {
    const auto [faResult, kmpResult] = createTest("abdcabdd", "bdd");
    assertVectorContains(faResult, {5});
    assertVectorContains(kmpResult, {5});
}

int main() {
    testEmptyTextEmptyPattern();
    testTextWithEmptyPattern();
    testEmptyTextWithPattern();
    testTextWithPattern();
    testTextWithRepeatingPattern();
    testTextWithNothingButPattern();
    testTextWithPatternAtTheEnd();

    std::cout << "All tests passed!\n";

    return 0;
}