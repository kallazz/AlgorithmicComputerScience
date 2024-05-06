// g++ runExperiment.cpp select.cpp randomVectorGenerator.cpp randomizedSelect.cpp utils.cpp binarySearch.cpp -O3

#include "binarySearch.hpp"
#include "randomizedSelect.hpp"
#include "select.hpp"
#include "randomVectorGenerator.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>

constexpr int EXPERIMENT_REPEATS = 50;

void runFirstExperiment() {
    std::ofstream comparisonsFile("plots/comparisons.txt");
    std::ofstream swapsFile("plots/swaps.txt");
    std::ofstream comparisonsOverNFile("plots/comparisonsOverN.txt");
    std::ofstream swapsOverNFile("plots/swapsOverN.txt");

    float selectComparisons;
    float selectSwaps;
    float randomizedSelectComparisons;
    float randomizedSelectSwaps;

    int comparisons, swaps;
    std::mt19937 generator(std::random_device{}());

    for (int currentN = 100; currentN <= 50000; currentN += 100) {
        std::cout << "Current N: " << currentN << '\n';

        std::uniform_int_distribution<int> dist(1, currentN);
        selectComparisons = 0;
        selectSwaps = 0;
        randomizedSelectComparisons = 0;
        randomizedSelectSwaps = 0;

        for (int i = 0; i < EXPERIMENT_REPEATS; i++) {
            const int randomOrderStatistic = dist(generator);
            std::vector<int> randomVector = generateRandomVector(currentN);
            std::vector<int> randomVectorCopy = randomVector;

            comparisons = 0;
            swaps = 0;
            select(randomVector, 0, currentN - 1, randomOrderStatistic , comparisons, swaps);
            selectComparisons += comparisons;
            selectSwaps += swaps;

            comparisons = 0;
            swaps = 0;
            randomizedSelect(randomVectorCopy, 0, currentN - 1, randomOrderStatistic, comparisons, swaps);
            randomizedSelectComparisons += comparisons;
            randomizedSelectSwaps += swaps;
        }

        selectComparisons /= EXPERIMENT_REPEATS;
        selectSwaps /= EXPERIMENT_REPEATS;
        randomizedSelectComparisons /= EXPERIMENT_REPEATS;
        randomizedSelectSwaps /= EXPERIMENT_REPEATS;

        comparisonsFile << currentN << " " << selectComparisons << " " << randomizedSelectComparisons << '\n';
        swapsFile << currentN << " " << selectSwaps << " " << randomizedSelectSwaps << '\n';
        comparisonsOverNFile << currentN << " " << selectComparisons / currentN << " " << randomizedSelectComparisons / currentN << '\n';
        swapsOverNFile << currentN << " " << selectSwaps / currentN << " " << randomizedSelectSwaps / currentN << '\n';
    }

    comparisonsFile.close();
    swapsFile.close();
    comparisonsOverNFile.close();
    swapsOverNFile.close();

}

void runSecondExperiment() {
    std::ofstream comparisonsFile("plots/arraySizesComparisons.txt");
    std::ofstream swapsFile("plots/arraySizesSwaps.txt");
    std::ofstream durationsFile("plots/arraySizesDurations.txt");

    const std::vector<int> arraySizesToCheck = {3, 5, 7, 9};
    std::vector<float> totalComparisons = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> totalSwaps = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<std::chrono::nanoseconds> totalDurations = {
        std::chrono::nanoseconds(0), std::chrono::nanoseconds(0), std::chrono::nanoseconds(0), std::chrono::nanoseconds(0)
    };

    int comparisons, swaps;
    std::mt19937 generator(std::random_device{}());

    for (int currentN = 100; currentN <= 50000; currentN += 100) {
        std::cout << "Current N: " << currentN << '\n';

        std::uniform_int_distribution<int> dist(1, currentN);

        for (int i = 0; i < EXPERIMENT_REPEATS; i++) {
            const int randomOrderStatistic = dist(generator);
            std::vector<int> randomVector = generateRandomVector(currentN);

            for (int j = 0; j < arraySizesToCheck.size(); j++) {
                std::vector<int> randomVectorCopy = randomVector;
                comparisons = 0;
                swaps = 0;

                auto startTime = std::chrono::steady_clock::now();
                select(randomVectorCopy, 0, currentN - 1, randomOrderStatistic, comparisons, swaps, arraySizesToCheck[j]);
                auto endTime = std::chrono::steady_clock::now();

                totalComparisons[j] += comparisons;
                totalSwaps[j] += swaps;
                totalDurations[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
            }
        }

        for (int i = 0; i < arraySizesToCheck.size(); i++) {
            totalComparisons[i] /= EXPERIMENT_REPEATS;
            totalSwaps[i] /= EXPERIMENT_REPEATS;
            totalDurations[i] /= EXPERIMENT_REPEATS;
        }

        comparisonsFile << currentN << " ";
        swapsFile << currentN << " ";
        durationsFile << currentN << " ";
        for (int i = 0; i < arraySizesToCheck.size(); i++) {
            comparisonsFile << totalComparisons[i] << " ";
            swapsFile << totalSwaps[i] << " ";
            durationsFile << totalDurations[i].count() << " ";
        }
        comparisonsFile << "\n";
        swapsFile << "\n";
        durationsFile << "\n";
    }

    comparisonsFile.close();
    swapsFile.close();
    durationsFile.close();
}

void runThirdExpertiment() {
    const int scenariosToCheck = 5;

    std::ofstream comparisonsFile("plots/binarySearchComparisons.txt");
    std::ofstream durationsFile("plots/binarySearchDurations.txt");

    std::vector<float> totalComparisons = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<std::chrono::nanoseconds> totalDurations = {
        std::chrono::nanoseconds(0), std::chrono::nanoseconds(0), std::chrono::nanoseconds(0), std::chrono::nanoseconds(0), std::chrono::nanoseconds(0)
    };

    int comparisons;
    std::mt19937 generator(std::random_device{}());

    for (int currentN = 1000; currentN <= 100000; currentN += 1000) {
        std::cout << "Current N: " << currentN << '\n';

        std::uniform_int_distribution<int> dist(0, currentN - 1);

        const int closeFactor = currentN / 10;
        for (int i = 0; i < EXPERIMENT_REPEATS; i++) {
            const std::vector<int> randomVector = generateRandomAscendingVector(currentN);
            const int closeLeftElement = randomVector[closeFactor];
            const int closeMiddleElement = randomVector[randomVector.size() / 2 + closeFactor];
            const int closeRightElement = randomVector[randomVector.size() - closeFactor];
            const int notInVectorElement = randomVector[randomVector.size() - 1] + 1;
            const int randomElement = randomVector[dist(generator)];
            const int elementsToCheck[scenariosToCheck] = {closeLeftElement, closeMiddleElement, closeRightElement, notInVectorElement, randomElement};

            for (int j = 0; j < scenariosToCheck; j++) {
                comparisons = 0;

                auto startTime = std::chrono::steady_clock::now();
                binarySearch(randomVector, 0, currentN - 1, elementsToCheck[j], comparisons);
                auto endTime = std::chrono::steady_clock::now();

                totalComparisons[j] += comparisons;
                totalDurations[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
            }
        }

        for (int i = 0; i < scenariosToCheck; i++) {
            totalComparisons[i] /= EXPERIMENT_REPEATS;
            totalDurations[i] /= EXPERIMENT_REPEATS;
        }

        comparisonsFile << currentN << " ";
        durationsFile << currentN << " ";
        for (int i = 0; i < scenariosToCheck; i++) {
            comparisonsFile << totalComparisons[i] << " ";
            durationsFile << totalDurations[i].count() << " ";
        }
        const float masterTheoremApproximation = log10(currentN);
        comparisonsFile << masterTheoremApproximation << "\n";
        durationsFile << "\n";
    }

    comparisonsFile.close();
    durationsFile.close();
}

int main() {
    runFirstExperiment();
    runSecondExperiment();
    runThirdExpertiment();

    return 0;
}