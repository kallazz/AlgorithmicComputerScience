#include "Graph.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>

Graph::Graph(const int numberOfVertices)
    : numberOfVertices_(numberOfVertices), adjacencyList_(std::vector<std::vector<Edge>>(numberOfVertices)) {}

Graph Graph::createHypercube(const int size) {
    const int numberOfVertices = 1 << size; // 2^size
    Graph hypercube(numberOfVertices);

    std::mt19937 mt(std::random_device{}());

    for (int vertex = 0; vertex < numberOfVertices; vertex++) {

        for (int dimension = 0; dimension < size; dimension++) {
            const int neighbor = vertex | (1 << dimension); // neighbor's index differs by exactly one bit from vertex

            if (vertex == neighbor) {
                continue;
            }

            const int vertexHammingWeight = __builtin_popcount(vertex);
            const int vertexNumberOfZeroes = size - vertexHammingWeight;

            const int neighborHammingWeight = __builtin_popcount(neighbor);
            const int neighborNumberOfZeroes = size - neighborHammingWeight;

            const int upperBound = 1 << std::max({vertexHammingWeight, vertexNumberOfZeroes, neighborHammingWeight, neighborNumberOfZeroes});

            std::uniform_int_distribution distribution(1, upperBound);

            hypercube.addEdge(vertex, neighbor, distribution(mt));
        }
    }

    return hypercube;
}

Graph Graph::createBipartiteGraph(const int size, const int degree) {
    std::mt19937 mt(std::random_device{}());

    const int initialNumberOfVertices = 1 << (size + 1);
    Graph bipartiteGraph(initialNumberOfVertices + 2); // + 2 is for the source and sink vertices

    for (int i = 0; i < initialNumberOfVertices / 2; i++) {
        std::vector<int> neighborCandidates(initialNumberOfVertices / 2);
        std::iota(std::begin(neighborCandidates), std::end(neighborCandidates), initialNumberOfVertices / 2); 
        std::shuffle(neighborCandidates.begin(), neighborCandidates.end(), mt);
        
        for (int j = 0; j < degree; j++) {
            bipartiteGraph.addEdge(i, neighborCandidates[j], 1);
        }
    }

    const int sourceVertex = initialNumberOfVertices;
    for (int i = 0; i < initialNumberOfVertices / 2; i++) {
        bipartiteGraph.addEdge(sourceVertex, i, 1);
    }

    const int sinkVertex = initialNumberOfVertices + 1;
    for (int i = initialNumberOfVertices / 2; i < initialNumberOfVertices; i++) {
        bipartiteGraph.addEdge(i, sinkVertex, 1);
    }

    return bipartiteGraph;
}

void Graph::addEdge(const int vertex1, const int vertex2, const int capacity) {
    adjacencyList_[vertex1].push_back(Edge(vertex1, vertex2, capacity, 0, adjacencyList_[vertex2].size()));
    adjacencyList_[vertex2].push_back(Edge(vertex2, vertex1, 0, 0, adjacencyList_[vertex1].size() - 1)); // reverse edge
}

int Graph::getNumberOfVertices() const {
    return numberOfVertices_;
}

std::vector<std::vector<Edge>> &Graph::getAdjacencyList() {
    return adjacencyList_;
}
