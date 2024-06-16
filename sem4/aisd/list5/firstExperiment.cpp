#include <chrono>
#include <fstream>
#include <iostream>

#include "Graph.hpp"

constexpr int N_MIN = 10;
constexpr int N_MAX = 1000;
constexpr int STEP = 10;
constexpr int EXPERIMENT_REPEATS = 10;

void runExperiment() {
    std::ofstream outputFile("plots/durations.txt");

    for (int currentN = N_MIN; currentN <= N_MAX; currentN += STEP) {
        std::cout << "Current N: " << currentN << '\n';

        std::chrono::nanoseconds kruskalDuration = std::chrono::nanoseconds(0);
        std::chrono::nanoseconds primDuration = std::chrono::nanoseconds(0);

        for (int i = 0; i < EXPERIMENT_REPEATS; i++) {
            Graph graph = Graph::generateRandomCompleteGraph(currentN);

            const auto kruskalStartTime = std::chrono::steady_clock::now();
            graph.generateKruskalsMinimumSpanningTree();
            const auto kruskalEndTime = std::chrono::steady_clock::now();

            const auto primStartTime = std::chrono::steady_clock::now();
            graph.generatePrimsMinimumSpanningTree();
            const auto primEndTime = std::chrono::steady_clock::now();

            kruskalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(kruskalEndTime - kruskalStartTime);
            primDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(primEndTime - primStartTime);
        }

        kruskalDuration /= EXPERIMENT_REPEATS;
        primDuration /= EXPERIMENT_REPEATS;

        outputFile << currentN << " " << kruskalDuration.count() << " " << primDuration.count() << '\n';
    }

    outputFile.close();
}

int main() {
    runExperiment();
}
