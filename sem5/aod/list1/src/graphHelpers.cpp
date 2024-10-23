#include "graphHelpers.hpp"
#include "Graph.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>

Graph createGraphFromFilename(const std::string &filename) {
    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("File " + filename + " not found");
    }

    std::ifstream file(filename);
    std::string text;

    getline(file, text);
    const bool isDirected = (text[0] == 'D');

    getline(file, text);
    const int numberOfVertices = std::stoi(text);

    getline(file, text);
    const int numberOfEdges = std::stoi(text);

    Graph graph(numberOfVertices, isDirected, true);

    for (int i = 0; i < numberOfEdges; i++) {
        getline(file, text, ' ');
        const int vertex1 = std::stoi(text);

        getline(file, text);
        const int vertex2 = std::stoi(text);

        graph.addEdge(vertex1, vertex2);
    }

    return graph;
}

void printStronglyConnectedComponents(const std::vector<std::vector<int>> &stronglyConnectedComponents, const int numberOfVertices) {
    std::cout << "Number of strongly connected components: " << stronglyConnectedComponents.size() << '\n';

    std::cout << "Numer of vertices in each component:\n";
    for (const auto &component : stronglyConnectedComponents) {
        std::cout << component.size();

        if (numberOfVertices <= 200) {
        std::cout << ", vertices in component: ";
            for (const int vertex : component) {
                std::cout << vertex + 1 << " ";
            }

        }

        std::cout << '\n';
    }
}