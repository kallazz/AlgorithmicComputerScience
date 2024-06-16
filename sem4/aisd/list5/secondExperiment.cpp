#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "Graph.hpp"

constexpr int N_MIN = 10;
constexpr int N_MAX = 1000;
constexpr int STEP = 10;
constexpr int EXPERIMENT_REPEATS = 10;

void runExperiment() {
    std::ofstream outputFile("plots/rounds.txt");

    for (int currentN = N_MIN; currentN <= N_MAX; currentN += STEP) {
        std::cout << "Current N: " << currentN << '\n';

        long long averageRounds = 0;
        long long minRounds = 0;
        long long maxRounds = 0;

        for (int i = 0; i < EXPERIMENT_REPEATS; i++) {
            Graph graph = Graph::generateRandomCompleteGraph(currentN).generatePrimsMinimumSpanningTree();
            long long currentMin = std::numeric_limits<long long>::max();
            long long currentMax = std::numeric_limits<long long>::min();

            for (int node = 0; node < currentN; node++) {
                const auto [_, rounds] = graph.findShortestInfoSpreadOrder(node);

                averageRounds += rounds;
                currentMin = std::min(currentMin, static_cast<long long>(rounds));
                currentMax = std::max(currentMax, static_cast<long long>(rounds));
            }

            minRounds += currentMin;
            maxRounds += currentMax;
        }

        averageRounds /= (EXPERIMENT_REPEATS * currentN);
        minRounds /= EXPERIMENT_REPEATS;
        maxRounds /= EXPERIMENT_REPEATS;

        outputFile << currentN << " " << averageRounds << " " << minRounds << " " << maxRounds << '\n';
    }

    outputFile.close();
}

int main() {
    runExperiment();
}
