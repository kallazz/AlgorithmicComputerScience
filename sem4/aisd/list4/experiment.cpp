#include "BinarySearchTree.hpp"
#include "RedBlackTree.hpp"
#include "SplayTree.hpp"
#include "Tree.hpp"
#include "randomVectorGenerator.hpp"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

constexpr int TREE_TYPES = 3;
constexpr int EXPERIMENT_REPEATS = 20;

void runFirstExperiment(const std::function<std::vector<int>(int)> &generateVector, const std::string &additionalText) {
    std::string prefix;
    std::ofstream keyComparisonsFile("plots/keyComparisons" + additionalText + ".txt");
    std::ofstream pointerOperationsFile("plots/pointerOperations" + additionalText + ".txt");
    std::ofstream heightsFile("plots/heights" + additionalText + ".txt");
    std::ofstream maxesFile("plots/maxes" + additionalText + ".txt");

    long long keyComparisons[TREE_TYPES], pointerOperations[TREE_TYPES], heights[TREE_TYPES];
    long long maxKeyComparisons[TREE_TYPES], maxPointerOperations[TREE_TYPES], maxHeights[TREE_TYPES];

    for (int currentN = 10000; currentN <= 100000; currentN += 10000) {
        std::cout << prefix + " current " + additionalText + " N: " << currentN << '\n';

        for (int i = 0; i < TREE_TYPES; i++) {
            keyComparisons[i] = 0;
            pointerOperations[i] = 0;
            heights[i] = 0;
            maxKeyComparisons[i] = 0;
            maxPointerOperations[i] = 0;
            maxHeights[i] = 0;
        }

        for (int j = 0; j < EXPERIMENT_REPEATS; j++) {
            std::vector<int> keysToInsert = generateVector(currentN);
            std::vector<int> keysToDelete = generateRandomVector(currentN);
            BinarySearchTree bst;
            RedBlackTree redBlackTree;
            SplayTree splayTree;

            for (const auto &key : keysToInsert) {
                bst.insertNode(key);
                redBlackTree.insertNode(key);
                splayTree.insertNode(key);
            }
            for (const auto &key : keysToDelete) {
                bst.deleteNode(key);
                redBlackTree.deleteNode(key);
                splayTree.deleteNode(key);
            }

            keyComparisons[0] += bst.getKeyComparisons();
            keyComparisons[1] += redBlackTree.getPointerOperations();
            keyComparisons[2] += splayTree.getPointerOperations();
            pointerOperations[0] += bst.getPointerOperations();
            pointerOperations[1] += redBlackTree.getPointerOperations();
            pointerOperations[2] += splayTree.getPointerOperations();
            heights[0] += bst.height();
            heights[1] += redBlackTree.height();
            heights[2] += splayTree.height();

            maxKeyComparisons[0] = std::max(maxKeyComparisons[0], bst.getKeyComparisons());
            maxKeyComparisons[1] = std::max(maxKeyComparisons[1], redBlackTree.getKeyComparisons());
            maxKeyComparisons[2] = std::max(maxKeyComparisons[2], splayTree.getKeyComparisons());
            maxPointerOperations[0] = std::max(maxPointerOperations[0], bst.getPointerOperations());
            maxPointerOperations[1] = std::max(maxPointerOperations[1], redBlackTree.getPointerOperations());
            maxPointerOperations[2] = std::max(maxPointerOperations[2], splayTree.getPointerOperations());
            maxHeights[0] = std::max(maxHeights[0], static_cast<long long>(bst.height()));
            maxHeights[1] = std::max(maxHeights[1], static_cast<long long>(redBlackTree.height()));
            maxHeights[2] = std::max(maxHeights[2], static_cast<long long>(splayTree.height()));
        }

        for (int i = 0; i < TREE_TYPES; i++) {
            keyComparisons[i] /= EXPERIMENT_REPEATS;
            pointerOperations[i] /= EXPERIMENT_REPEATS;
            heights[i] /= EXPERIMENT_REPEATS;
        }

        keyComparisonsFile << currentN << " " << keyComparisons[0] << " " << keyComparisons[1] << " "
                           << keyComparisons[2] << '\n';
        pointerOperationsFile << currentN << " " << pointerOperations[0] << " " << pointerOperations[1] << " "
                              << pointerOperations[2] << '\n';
        heightsFile << currentN << " " << heights[0] << " " << heights[1] << " " << heights[2] << '\n';

        maxesFile << currentN << ":" << "    " << maxKeyComparisons[0] << " " << maxKeyComparisons[1] << " "
                  << maxKeyComparisons[2] << "\n\t" << maxPointerOperations[0] << " " << maxPointerOperations[1] << " "
                  << maxPointerOperations[2] << "\n\t" << maxHeights[0] << " " << maxHeights[1] << " " << maxHeights[2]
                  << "\n\t";
    }

    keyComparisonsFile.close();
    pointerOperationsFile.close();
    heightsFile.close();
}

int main() {
    std::function<std::vector<int>(int)> generateRandomAscendingVectorFunction = generateRandomAscendingVector;
    std::function<std::vector<int>(int)> generateRandomVectorFunction = generateRandomVector;
    std::thread firstExperimentAscending(runFirstExperiment, generateRandomAscendingVectorFunction, "Ascending");
    std::thread firstExperimentRandom(runFirstExperiment, generateRandomVectorFunction, "");
    firstExperimentAscending.join();
    firstExperimentRandom.join();

    return 0;
}