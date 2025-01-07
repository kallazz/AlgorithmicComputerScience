#include <chrono>
#include <iostream>
#include <fstream>

#include "algorithms.hpp"
#include "Graph.hpp"

const std::string OUTPUT_DIRECTORY = "../experimentOutput/";
constexpr int NUMBER_OF_REPEATS = 10;

void runExperiment() {
    std::ofstream resultsFile(OUTPUT_DIRECTORY + "edmondsKarpResults.csv");
    resultsFile << "Hypercube Size,Duration,Max Flow,Number of Augmenting Paths\n";

    for (int size = 1; size <= 16; size++) {
        std::chrono::nanoseconds totalDuration = std::chrono::nanoseconds(0);
        long long totalMaxFlow = 0;
        long long totalAmountOfAugmentingPathsFound = 0;

        for (int i = 0; i < NUMBER_OF_REPEATS; i++) {
            Graph hypercube = Graph::createHypercube(size);
            const auto startTime = std::chrono::high_resolution_clock::now();
            const auto [maxFlow, amountOfAugmentingPathsFound] = edmondsKarp(hypercube, 0, (1 << size) - 1);
            const auto endTime = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

            totalDuration += duration;
            totalMaxFlow += maxFlow;
            totalAmountOfAugmentingPathsFound += amountOfAugmentingPathsFound;
            std::cout << i + 1 << " times completed for size " << size << '\n';
        }

        resultsFile << size << "," << totalDuration.count() / NUMBER_OF_REPEATS << ","
            << totalMaxFlow / NUMBER_OF_REPEATS << "," << totalAmountOfAugmentingPathsFound / NUMBER_OF_REPEATS << "\n";

        std::cout << "Tests for size " << size << " finished\n";
    }

    resultsFile.close();
}

int main() {
    runExperiment();

    return 0;
}
