
#include "SplayTree.hpp"
#include "randomVectorGenerator.hpp"

#include <iostream>

constexpr int VECTOR_SIZE = 50;

int main() {
    std::cout << "Random ascending inserts, random deletes\n";
    std::vector<int> keysToInsert = generateRandomAscendingVector(VECTOR_SIZE);
    std::vector<int> keysToDelete = generateRandomVector(VECTOR_SIZE);
    SplayTree firstSplayTree;
    firstSplayTree.setPrintFlag(true);

    for (const auto &key : keysToInsert) {
        firstSplayTree.insertNode(key);
        firstSplayTree.print();
    }
    for (const auto &key : keysToDelete) {
        firstSplayTree.deleteNode(key);
        firstSplayTree.print();
    }

    std::cout << "Random inserts, random deletes\n";
    keysToInsert = generateRandomVector(VECTOR_SIZE);
    keysToDelete = generateRandomVector(VECTOR_SIZE);
    SplayTree secondSplayTree;
    secondSplayTree.setPrintFlag(true);

    for (const auto &key : keysToInsert) {
        secondSplayTree.insertNode(key);
        secondSplayTree.print();
    }
    for (const auto &key : keysToDelete) {
        secondSplayTree.deleteNode(key);
        secondSplayTree.print();
    }

    return 0;
}


