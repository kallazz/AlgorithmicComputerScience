#include <chrono>
#include <queue>
#include <vector>
#include <iostream>

#include "algorithms.hpp"
#include "Graph.hpp"

int main(int argc, char const *argv[]) {
    // Graph graph = Graph::createHypercube(3);

    // int counter = 0;
    // for (const auto neighbors : graph.getAdjacencyList()) {
    //     std::cout << counter;
    //     std::cout << ", Neighors:";

    //     for (const auto neighbor : neighbors) {
    //         std::cout << neighbor.sinkVertex << ", ";
    //     }
    //     std::cout << '\n';

    //     counter++;
    // }

    bool wasSizeFlagProvided = false;
    bool wasPrintFlowFlagProvided = false;
    int size = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i] == "--size" && i + 1 < argc) {
            wasSizeFlagProvided = true;
            size = std::stoi(argv[i + 1]);
            i++;
        }

        if (argv[i] == "--printFlow") {
            wasPrintFlowFlagProvided = true;
        } 
    }


    Graph hypercube = Graph::createHypercube(size);

    const auto startTime = std::chrono::high_resolution_clock::now();
    const auto [maxFlow, amountOfAugmentingPathsFound] = edmondsKarp(hypercube, 0, (1 << size) - 1);
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto duration = (endTime - startTime).count();

    

    return 0;
}
