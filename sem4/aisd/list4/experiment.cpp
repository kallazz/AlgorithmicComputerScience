#include "BinarySearchTree.hpp"
#include "randomVectorGenerator.hpp"

#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

constexpr int EXPERIMENT_REPEATS = 20;

void runFirstExperiment() {
    std::ofstream keyComparisonsFile("plots/keyComparisons.txt");
    std::ofstream pointerOperationsFile("plots/pointerOperations.txt");
    std::ofstream heightsFile("plots/heights.txt");

    int keyComparisons, pointerOperations, heights, maxKeyComparisons, maxPointerOperations, maxHeights;

    for (int currentN = 10000; currentN <= 100000; currentN += 10000) {
        std::cout << "Current N: " << currentN << '\n';

        keyComparisons = 0;
        pointerOperations = 0;
        heights = 0;
        maxKeyComparisons = 0;
        maxPointerOperations = 0;
        maxHeights = 0;

        for (int j = 0; j < EXPERIMENT_REPEATS; j++) {
            int keyComparisonsBefore = keyComparisons;
            int pointerOperationsBefore = pointerOperations;
            std::vector<int> keysToInsert = generateRandomAscendingVector(currentN);
            std::vector<int> keysToDelete = generateRandomVector(currentN);
            BinarySearchTree bst;

            for (const auto &key : keysToInsert) {
                bst.insertNode(key, keyComparisons, pointerOperations);
            }
            for (const auto &key : keysToDelete) {
                bst.deleteNode(key, keyComparisons, pointerOperations);
            }

            int currentHeight = bst.height();
            heights += currentHeight;

            maxKeyComparisons = std::max(maxKeyComparisons, keyComparisons - keyComparisonsBefore);
            maxPointerOperations = std::max(maxPointerOperations, pointerOperations - pointerOperationsBefore);
            maxHeights = std::max(maxHeights, currentHeight);
        }

        keyComparisons /= EXPERIMENT_REPEATS;
        pointerOperations /= EXPERIMENT_REPEATS;
        heights /= EXPERIMENT_REPEATS;

        keyComparisonsFile << currentN << " " << keyComparisons << " " << maxKeyComparisons << '\n';
        pointerOperationsFile << currentN << " " << pointerOperations << " " << maxPointerOperations << '\n';
        heightsFile << currentN << " " << heights << " " << maxHeights << '\n';
    }

    keyComparisonsFile.close();
    pointerOperationsFile.close();
    heightsFile.close();
}

int main() {
    std::thread firstExperiment(runFirstExperiment);
    firstExperiment.join();

    return 0;
}