#include "RedBlackTree.hpp"
#include "randomVectorGenerator.hpp"

#include <iostream>

constexpr int VECTOR_SIZE = 50;

int main() {
    std::cout << "Random ascending inserts, random deletes\n";
    std::vector<int> keysToInsert = generateRandomAscendingVector(VECTOR_SIZE);
    std::vector<int> keysToDelete = generateRandomVector(VECTOR_SIZE);
    RedBlackTree firstRBT;
    long long keyComparisons, pointerOperations;

    for (const auto &key : keysToInsert) {
        firstRBT.insertNode(key, true);
        firstRBT.print();
    }
    for (const auto &key : keysToDelete) {
        firstRBT.deleteNode(key, true);
        firstRBT.print();
    }

    std::cout << "Random inserts, random deletes\n";
    keysToInsert = generateRandomVector(VECTOR_SIZE);
    keysToDelete = generateRandomVector(VECTOR_SIZE);
    RedBlackTree secondRBT;

    for (const auto &key : keysToInsert) {
        secondRBT.insertNode(key, true);
        secondRBT.print();
    }
    for (const auto &key : keysToDelete) {
        secondRBT.deleteNode(key, true);
        secondRBT.print();
    }

    return 0;
}
