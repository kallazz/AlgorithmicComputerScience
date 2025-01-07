#include "Graph.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>

Graph::Graph(const long long numberOfVertices, const bool isDirected)
    : numberOfVertices_(numberOfVertices), numberOfEdges_(0), isDirected_(isDirected),
      adjacencyList_(std::vector<std::vector<Edge>>(numberOfVertices)) {}

Graph Graph::createHypercube(const long long size) {
    const long long numberOfVertices = 1 << size; // 2^size
    Graph hypercube(numberOfVertices, true);

    std::mt19937 mt(std::random_device{}());

    for (long long vertex = 0; vertex < numberOfVertices; vertex++) {

        for (long long dimension = 0; dimension < size; dimension++) {
            const long long neighbor = vertex | (1 << dimension); // neighbor's index differs by exactly one bit from vertex

            if (vertex == neighbor) {
                continue;
            }

            const long long vertexHammingWeight = __builtin_popcount(size);
            const long long vertexNumberOfZeroes = dimension - vertexHammingWeight;

            const long long neighborHammingWeight = __builtin_popcount(size);
            const long long neighborNumberOfZeroes = dimension - neighborHammingWeight;

            const long long upperBound = 1 << std::max({vertexHammingWeight, vertexNumberOfZeroes, neighborHammingWeight, neighborNumberOfZeroes});

            std::uniform_int_distribution<long long> distribution(1, upperBound);

            hypercube.addEdge(vertex, neighbor, distribution(mt));
        }
    }

    return hypercube;
}

void Graph::addEdge(const long long vertex1, const long long vertex2, const long long capacity) {
    numberOfEdges_++;

    if (isDirected_) {
        adjacencyList_[vertex1].push_back(Edge(vertex1, vertex2, capacity, 0, adjacencyList_[vertex2].size()));
        adjacencyList_[vertex2].push_back(Edge(vertex2, vertex1, 0, 0, adjacencyList_[vertex1].size() - 1)); // reverse edge
        return;
    }

    // adjacencyList_[vertex1].push_back(Edge(vertex1, vertex2, capacity));
    // adjacencyList_[vertex2].push_back(Edge(vertex2, vertex1, capacity));
}

bool Graph::isDirected() const {
    return isDirected_;
}

long long Graph::getNumberOfVertices() const {
    return numberOfVertices_;
}

long long Graph::getNumberOfEdges() const {
    return numberOfEdges_;
}

std::vector<std::vector<Edge>> &Graph::getAdjacencyList() {
    return adjacencyList_;
}
