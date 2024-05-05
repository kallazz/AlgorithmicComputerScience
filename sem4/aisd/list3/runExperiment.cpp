// g++ runExperiment.cpp select.cpp randomVectorGenerator.cpp randomizedSelect.cpp utils.cpp -O2

#include "randomizedSelect.hpp"
#include "select.hpp"
#include "randomVectorGenerator.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

constexpr int EXPERIMENT_REPEATS = 50;

int main() {
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

        for (int j = 0; j < EXPERIMENT_REPEATS; j++) {
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

    return 0;
}