#include "BinarySearchTree.hpp"
#include "RedBlackTree.hpp"
#include "Tree.hpp"
#include "randomVectorGenerator.hpp"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

constexpr int EXPERIMENT_REPEATS = 20;

void runFirstExperiment(const std::function<std::vector<int>(int)> &generateVector, const std::string &additionalText) {
    std::string prefix;
    std::ofstream keyComparisonsAscendingFile("plots/keyComparisons" + additionalText + ".txt");
    std::ofstream pointerOperationsAscendingFile("plots/pointerOperations" + additionalText + ".txt");
    std::ofstream heightsAscendingFile("plots/heights" + additionalText + ".txt");

    long long BSTKeyComparisons, BSTPointerOperations, BSTHeights, maxKeyComparisons, maxPointerOperations, maxHeights;
    long long RSTKeyComparisons, RSTPointerOperations, RSTHeights;

    for (int currentN = 10000; currentN <= 40000; currentN += 10000) {
        std::cout << prefix + " current " + additionalText + " N: " << currentN << '\n';

        BSTKeyComparisons = 0;
        BSTPointerOperations = 0;
        BSTHeights = 0;
        RSTKeyComparisons = 0;
        RSTPointerOperations = 0;
        RSTHeights = 0;
        maxKeyComparisons = 0;
        maxPointerOperations = 0;
        maxHeights = 0;

        for (int j = 0; j < EXPERIMENT_REPEATS; j++) {
            std::vector<int> keysToInsert = generateVector(currentN);
            std::vector<int> keysToDelete = generateRandomVector(currentN);
            BinarySearchTree bst;
            RedBlackTree rst;

            for (const auto &key : keysToInsert) {
                bst.insertNode(key);
                rst.insertNode(key);
            }
            for (const auto &key : keysToDelete) {
                bst.deleteNode(key);
                rst.deleteNode(key);
            }

            BSTKeyComparisons += bst.getKeyComparisons();
            BSTPointerOperations += bst.getPointerOperations();
            RSTKeyComparisons += rst.getKeyComparisons();
            RSTPointerOperations += rst.getPointerOperations();

            int currentBSTHeight = bst.height();
            int currentRSTHeight = rst.height();
            BSTHeights += currentBSTHeight;
            RSTHeights += currentRSTHeight;

            maxKeyComparisons = std::max(maxKeyComparisons, bst.getKeyComparisons());
            maxPointerOperations = std::max(maxPointerOperations, bst.getPointerOperations());
            maxHeights = std::max(maxHeights, static_cast<long long>(currentBSTHeight));
        }

        BSTKeyComparisons /= EXPERIMENT_REPEATS;
        BSTPointerOperations /= EXPERIMENT_REPEATS;
        BSTHeights /= EXPERIMENT_REPEATS;
        RSTKeyComparisons /= EXPERIMENT_REPEATS;
        RSTPointerOperations /= EXPERIMENT_REPEATS;
        RSTHeights /= EXPERIMENT_REPEATS;

        keyComparisonsAscendingFile << currentN << " " << BSTKeyComparisons << " " << RSTKeyComparisons << '\n';
        pointerOperationsAscendingFile << currentN << " " << BSTPointerOperations << " " << RSTPointerOperations << '\n';
        heightsAscendingFile << currentN << " " << BSTHeights << " " << RSTHeights << '\n';
    }

    keyComparisonsAscendingFile.close();
    pointerOperationsAscendingFile.close();
    heightsAscendingFile.close();
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