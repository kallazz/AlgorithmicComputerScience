#include "Graph.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

constexpr int N_MIN = 10;
constexpr int N_MAX = 500;
constexpr int STEP = 10;
constexpr int EXPERIMENT_REPEATS = 20;

void runExperiment() {
    std::string result = "";
    std::ofstream outputFile("plots/durations.txt");

    for (int currentN = N_MIN; currentN <= N_MAX; currentN += STEP) {
        std::cout << "Current N: " << currentN << '\n';

        std::chrono::nanoseconds kruskalDuration = std::chrono::nanoseconds(0);
        std::chrono::nanoseconds primDuration = std::chrono::nanoseconds(0);

        for (int i = 0; i < EXPERIMENT_REPEATS; i++) {
            Graph graph = Graph::generateRandomCompleteGraph(currentN);

            auto kruskalStartTime = std::chrono::steady_clock::now();
            graph.generateKruskalsMinimumSpanningTree();
            auto kruskalEndTime = std::chrono::steady_clock::now();

            auto primStartTime = std::chrono::steady_clock::now();
            graph.generatePrimsMinimumSpanningTree();
            auto primEndTime = std::chrono::steady_clock::now();

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
