#include <iomanip>
#include <iostream>

#include "Graph.hpp"

constexpr int GRAPH_SIZE = 10;

void printAdjacencyMatrix(const std::vector<std::vector<double>> &adjacencyMatrix) {
    for (const auto &row : adjacencyMatrix) {
        for (const auto &element : row) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << element;
        }
        std::cout << '\n';
    }
}

int main() {
    Graph graph = Graph::generateRandomCompleteGraph(GRAPH_SIZE);

    std::cout << "Radom complete graph:\n";
    printAdjacencyMatrix(graph.getAdjecencyMatrix());

    std::cout << "\nKruskal's minimum spanning tree:\n";
    printAdjacencyMatrix(graph.generateKruskalsMinimumSpanningTree().getAdjecencyMatrix());

    std::cout << "\nPrim's minimum spanning tree:\n";
    printAdjacencyMatrix(graph.generatePrimsMinimumSpanningTree().getAdjecencyMatrix());

    std::cout << "\nOrder of shortest information spread starting from node 0:\n";
    const auto [order, roundsLeft] = graph.generatePrimsMinimumSpanningTree().findShortestInfoSpreadOrder(0);
    for (int i = 0; i < GRAPH_SIZE; i++) {
        std::cout << "Node " << i << " -> next nodes: [ ";
        for (const auto node : order[i]) {
            std::cout << node << ' ';
        }
        std::cout << "], rounds left: " << roundsLeft[i] << '\n';
    }
}