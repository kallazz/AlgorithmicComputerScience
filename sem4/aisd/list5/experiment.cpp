#include "completeGraphGenerator.hpp"
#include "minimumSpanningTree.hpp"
#include "Graph.hpp"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

constexpr int EXPERIMENT_REPEATS = 10;

std::string runExperiment(const std::function<std::vector<int>(int)> &algoritm) {
    std::string result = "";

    for (int currentN = 10000; currentN <= 100000; currentN += 10000) {
        std::cout << "Current N: " << currentN << '\n';

        std::chrono::nanoseconds duration = std::chrono::nanoseconds(0);

        for (int j = 0; j < EXPERIMENT_REPEATS; j++) {
            auto startTime = std::chrono::steady_clock::now();
            algoritm(12345);
            auto endTime = std::chrono::steady_clock::now();

            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        }

        duration /= EXPERIMENT_REPEATS;

        result += std::to_string(currentN) + " " + std::to_string(duration.count()) + '\n';
    }

    return result;
}

int main() {
    // std::function<std::vector<int>(int)> generateRandomAscendingVectorFunction = generateRandomAscendingVector;
    // std::function<std::vector<int>(int)> generateRandomVectorFunction = generateRandomVector;
    // std::thread experimentPrim(runExperiment, generateRandomAscendingVectorFunction);
    // std::thread experimentKruskal(runExperiment, generateRandomVectorFunction);
    // experimentPrim.join();
    // experimentKruskal.join();

    Graph graph = Graph::generateRandomCompleteGraph(10);
    graph.addWeightedEdge(20, 30, 5.5);

    std::cout << graph.getEdges()[45].weight << '\n';
}