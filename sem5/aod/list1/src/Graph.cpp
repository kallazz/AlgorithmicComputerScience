#include "Graph.hpp"

Graph::Graph(const int numberOfVertices, const bool isDirected, const bool isIndexedFromOne)
    : numberOfVertices_(numberOfVertices), numberOfEdges_(0), isDirected_(isDirected),
      isIndexedFromOne_(isIndexedFromOne), adjacencyList_(std::vector<std::vector<int>>(numberOfVertices + 1)) {}

Graph::Graph(const int numberOfVertices, const bool isDirected, const bool isIndexedFromOne,
             const std::vector<std::pair<int, int>> &edges)
    : Graph(numberOfVertices, isDirected, isIndexedFromOne) {

    for (const auto &[vertex1, vertex2] : edges) {
        addEdge(vertex1, vertex2);
    }
}

void Graph::addEdge(int vertex1, int vertex2) {
    numberOfEdges_++;

    if (isIndexedFromOne_) {
        vertex1--;
        vertex2--;
    }

    if (isDirected_) {
        adjacencyList_[vertex1].push_back(vertex2);
        return;
    }

    adjacencyList_[vertex1].push_back(vertex2);
    adjacencyList_[vertex2].push_back(vertex1);
}

bool Graph::isDirected() const {
    return isDirected_;
}

bool Graph::isIndexedFromOne() const {
    return isIndexedFromOne_;
}

int Graph::getNumberOfVertices() const {
    return numberOfVertices_;
}

int Graph::getNumberOfEdges() const {
    return numberOfEdges_;
}

const std::vector<std::vector<int>> &Graph::getAdjacencyList() const {
    return adjacencyList_;
}
