#include "Graph.hpp"

#include <random>

Graph::Graph(const int size) : size_(size) {}

Graph Graph::generateRandomCompleteGraph(const int size) {
    Graph graph(size);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            graph.addRandomWeightedEdge(i, j);
        }
    }

    return graph;
}


void Graph::addWeightedEdge(const int node1, const int node2, const double weight) {
    edges_.push_back(Edge(node1, node2, weight));
}

void Graph::addRandomWeightedEdge(const int node1, const int node2) {
    addWeightedEdge(node1, node2, generateRandomWeight());
}

std::vector<Edge> Graph::getEdges() const {
    return edges_;
}

double Graph::generateRandomWeight() const {
    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}