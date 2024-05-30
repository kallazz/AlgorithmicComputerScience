#include "BinarySearchTree.hpp"
#include "randomVectorGenerator.hpp"

#include <iostream>

constexpr int VECTOR_SIZE = 50;

int main() {
    std::cout << "Random ascending inserts, random deletes\n";
    std::vector<int> keysToInsert = generateRandomAscendingVector(VECTOR_SIZE);
    std::vector<int> keysToDelete = generateRandomVector(VECTOR_SIZE);
    BinarySearchTree firstBST;
    long long keyComparisons, pointerOperations;

    for (const auto &key : keysToInsert) {
        firstBST.insertNode(key, true);
        firstBST.print();
    }
    for (const auto &key : keysToDelete) {
        firstBST.deleteNode(key, true);
        firstBST.print();
    }

    std::cout << "Random inserts, random deletes\n";
    keysToInsert = generateRandomVector(VECTOR_SIZE);
    keysToDelete = generateRandomVector(VECTOR_SIZE);
    BinarySearchTree secondBST;

    for (const auto &key : keysToInsert) {
        secondBST.insertNode(key, true);
        secondBST.print();
    }
    for (const auto &key : keysToDelete) {
        secondBST.deleteNode(key, true);
        secondBST.print();
    }

    return 0;
}
