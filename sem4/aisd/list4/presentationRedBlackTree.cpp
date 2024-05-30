#include "RedBlackTree.hpp"
#include "randomVectorGenerator.hpp"

#include <iostream>

constexpr int VECTOR_SIZE = 50;

int main() {
    std::cout << "Random ascending inserts, random deletes\n";
    std::vector<int> keysToInsert = generateRandomAscendingVector(VECTOR_SIZE);
    std::vector<int> keysToDelete = generateRandomVector(VECTOR_SIZE);
    RedBlackTree firstRBT;
    firstRBT.setPrintFlag(true);

    for (const auto &key : keysToInsert) {
        firstRBT.insertNode(key);
        firstRBT.print();
    }
    for (const auto &key : keysToDelete) {
        firstRBT.deleteNode(key);
        firstRBT.print();
    }

    std::cout << "Random inserts, random deletes\n";
    keysToInsert = generateRandomVector(VECTOR_SIZE);
    keysToDelete = generateRandomVector(VECTOR_SIZE);
    RedBlackTree secondRBT;
    secondRBT.setPrintFlag(true);

    for (const auto &key : keysToInsert) {
        secondRBT.insertNode(key);
        secondRBT.print();
    }
    for (const auto &key : keysToDelete) {
        secondRBT.deleteNode(key);
        secondRBT.print();
    }

    return 0;
}
