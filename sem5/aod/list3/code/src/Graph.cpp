#include "Graph.hpp"

Graph::Graph(const int numberOfVertices, const bool isDirected)
    : numberOfVertices_(numberOfVertices), numberOfEdges_(0), isDirected_(isDirected), maxWeight_(0),
      adjacencyList_(std::vector<std::vector<std::pair<int, int>>>(numberOfVertices)) {}

Graph::Graph(const int numberOfVertices, const bool isDirected, const std::vector<std::tuple<int, int, int>> &edges)
    : Graph(numberOfVertices, isDirected) {

    for (const auto &[vertex1, vertex2, weight] : edges) {
        addEdge(vertex1, vertex2, weight);
    }
}

void Graph::addEdge(int vertex1, int vertex2, int weight) {
    numberOfEdges_++;
    maxWeight_ = std::max(weight, maxWeight_);

    if (isDirected_) {
        adjacencyList_[vertex1].push_back({vertex2, weight});
        return;
    }

    adjacencyList_[vertex1].push_back({vertex2, weight});
    adjacencyList_[vertex2].push_back({vertex1, weight});
}

bool Graph::isDirected() const {
    return isDirected_;
}

int Graph::getNumberOfVertices() const {
    return numberOfVertices_;
}

int Graph::getNumberOfEdges() const {
    return numberOfEdges_;
}

int Graph::getMaxWeight() const {
    return maxWeight_;
}

const std::vector<std::vector<std::pair<int, int>>> &Graph::getAdjacencyList() const {
    return adjacencyList_;
}
