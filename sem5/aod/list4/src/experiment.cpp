#include <chrono>
#include <iostream>
#include <fstream>

#include "algorithms.hpp"
#include "Graph.hpp"

const std::string OUTPUT_DIRECTORY = "./experimentOutput/";
constexpr int FIRST_EXPERIMENT_NUMBER_OF_REPEATS = 100;
constexpr int SECOND_EXPERIMENT_NUMBER_OF_REPEATS = 1000;

void runFirstExperiment(const int numberOfRepeats) {
    std::ofstream resultsFile(OUTPUT_DIRECTORY + "edmondsKarpResults.csv");
    resultsFile << "Hypercube Size,Duration,Max Flow,Number of Augmenting Paths\n";

    for (int size = 1; size <= 16; size++) {
        std::chrono::nanoseconds totalDuration = std::chrono::nanoseconds(0);
        long long totalMaxFlow = 0;
        long long totalAmountOfAugmentingPathsFound = 0;

        for (int i = 0; i < numberOfRepeats; i++) {
            Graph hypercube = Graph::createHypercube(size);
            const int sourceVertex = 0;
            const int sinkVertex = (1 << size) - 1;

            const auto startTime = std::chrono::high_resolution_clock::now();
            const auto [maxFlow, amountOfAugmentingPathsFound] = edmondsKarp(hypercube, sourceVertex, sinkVertex);
            const auto endTime = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

            totalDuration += duration;
            totalMaxFlow += maxFlow;
            totalAmountOfAugmentingPathsFound += amountOfAugmentingPathsFound;
            std::cout << i + 1 << " times completed for size " << size << '\n';
        }

        resultsFile << size << "," << totalDuration.count() / numberOfRepeats << ","
            << totalMaxFlow / numberOfRepeats << "," << totalAmountOfAugmentingPathsFound / numberOfRepeats << "\n";

        std::cout << "Tests for size " << size << " finished\n";
    }

    resultsFile.close();
}

void runSecondExperiment(const int numberOfRepeats) {
    std::ofstream resultsFile(OUTPUT_DIRECTORY + "maximumBipartiteMatchingResults.csv");
    resultsFile << "Graph Size,Degree,Duration,Max Matching Size\n";

    for (int k = 3; k <= 10; k++) {
        for (int i = 1; i <= k; i++) {
            std::chrono::nanoseconds totalDuration = std::chrono::nanoseconds(0);
            double totalMaxMatchingSize = 0;

            for (int j = 0; j <= numberOfRepeats; j++) {
                Graph graph = Graph::createBipartiteGraph(k, i);
                const int sourceVertex = 1 << (k + 1);
                const int sinkVertex = sourceVertex + 1;

                const auto startTime = std::chrono::high_resolution_clock::now();
                const auto [maxMatchingSize, _] = edmondsKarp(graph, sourceVertex, sinkVertex);
                const auto endTime = std::chrono::high_resolution_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

                totalDuration += duration;
                totalMaxMatchingSize += maxMatchingSize;
                std::cout << "Iteration for k=" << k << ", i=" << i << "\n";
            }

            resultsFile << k << "," << i << "," << totalDuration.count() / numberOfRepeats << "," << totalMaxMatchingSize / numberOfRepeats << '\n';
        }
    }

    resultsFile.close();
}

int main() {
    // runFirstExperiment(FIRST_EXPERIMENT_NUMBER_OF_REPEATS);
    runSecondExperiment(SECOND_EXPERIMENT_NUMBER_OF_REPEATS);

    return 0;
}
