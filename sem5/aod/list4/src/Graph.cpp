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

            const long long vertexHammingWeight = __builtin_popcount(vertex);
            const long long vertexNumberOfZeroes = size - vertexHammingWeight;

            const long long neighborHammingWeight = __builtin_popcount(neighbor);
            const long long neighborNumberOfZeroes = size - neighborHammingWeight;

            const long long upperBound = 1 << std::max({vertexHammingWeight, vertexNumberOfZeroes, neighborHammingWeight, neighborNumberOfZeroes});

            std::uniform_int_distribution<long long> distribution(1, upperBound);

            hypercube.addEdge(vertex, neighbor, distribution(mt));
        }
    }

    return hypercube;
}

Graph Graph::createBipartiteGraph(const long long size, const long long vertexDegree) {
    const long long numberOfVertices = 1 << (size + 1); // 2^(2 * size)
    Graph bipartiteGraph(numberOfVertices, false);

    std::mt19937 mt(std::random_device{}());

    std::uniform_int_distribution<long long> firstVertexSetDistribution(0, (2 << size) - 1);
    std::uniform_int_distribution<long long> secondVertexSetDistribution((2 << size), (1 << (2 * size)) - 1);

    for (long long vertex = 0; vertex < numberOfVertices; vertex++) {
        for (int i = 0; i < vertexDegree; i++) {
            const long long neighbor = (vertex <= (2 << size) - 1) ? secondVertexSetDistribution(mt) : firstVertexSetDistribution(mt);
            bipartiteGraph.addEdge(vertex, neighbor, 1);
        }
    }

    return bipartiteGraph;
}

void Graph::addEdge(const long long vertex1, const long long vertex2, const long long capacity) {
    numberOfEdges_++;

    if (isDirected_) {
        adjacencyList_[vertex1].push_back(Edge(vertex1, vertex2, capacity, 0, adjacencyList_[vertex2].size()));
        adjacencyList_[vertex2].push_back(Edge(vertex2, vertex1, 0, 0, adjacencyList_[vertex1].size() - 1)); // reverse edge
        return;
    }

    adjacencyList_[vertex1].push_back(Edge(vertex1, vertex2, capacity, 0, adjacencyList_[vertex2].size()));
    adjacencyList_[vertex2].push_back(Edge(vertex2, vertex1, capacity, 0, adjacencyList_[vertex1].size() - 1));
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
