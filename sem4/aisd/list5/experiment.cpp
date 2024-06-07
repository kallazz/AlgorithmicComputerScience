#include "Graph.hpp"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

constexpr int EXPERIMENT_REPEATS = 5;

void runExperiment(Graph (Graph::*minimumSpanningTreeAlgorithm)() const, const std::string &additionalText) {
    std::string result = "";
    std::ofstream outputFile("plots/" + additionalText + "Times.txt");

    for (int currentN = 10; currentN <= 100; currentN += 10) {
        std::cout << additionalText << " Current N: " << currentN << '\n';

        std::chrono::nanoseconds duration = std::chrono::nanoseconds(0);

        for (int j = 0; j < EXPERIMENT_REPEATS; j++) {
            Graph graph = Graph::generateRandomCompleteGraph(currentN);
            auto startTime = std::chrono::steady_clock::now();
            (graph.*minimumSpanningTreeAlgorithm)();
            auto endTime = std::chrono::steady_clock::now();

            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        }

        duration /= EXPERIMENT_REPEATS;

        outputFile << currentN << " " << duration.count() << '\n';
    }

    outputFile.close();
}

int main() {
    std::thread experimentKruskal(runExperiment, &Graph::getKruskalsMinimumSpanningTree, "Kruskal");
    std::thread experimentPrim(runExperiment, &Graph::getPrimsMinimumSpanningTree, "Prim");
    experimentKruskal.join();
    experimentPrim.join();
}
