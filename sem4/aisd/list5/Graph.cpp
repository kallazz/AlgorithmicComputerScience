#include "Graph.hpp"

#include <algorithm>
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

Graph Graph::getKruskalsMinimumSpanningTree() const {
    std::vector<int> parents;
    std::vector<int> ranks;
    for (int i = 0; i < size_; i++) {
        parents.push_back(i);
        ranks.push_back(0);
    }

    std::vector<Edge> edges = edges_;
    sortEdges(edges);

    Graph minimumSpanningTree(size_);
    for (const Edge &edge : edges) {
        if (find(edge.node1, parents) != find(edge.node2, parents)) {
            minimumSpanningTree.addWeightedEdge(edge.node1, edge.node2, edge.weight);
            unite(edge.node1, edge.node2, parents, ranks);
        }
    }

    return minimumSpanningTree;
}

Graph Graph::getPrimsMinimumSpanningTree() const {}

int Graph::find(const int node, std::vector<int> &parents) const {
    if (parents[node] != node) {
        parents[node] = find(parents[node], parents);
    }

    return parents[node];
}

void Graph::unite(const int node1, const int node2, std::vector<int> &parents, std::vector<int> &ranks) const {
    const int root1 = find(node1, parents);
    const int root2 = find(node2, parents);

    if (root1 != root2) {
        if (ranks[root1] < ranks[root2]) {
            parents[root1] = root2;
        } else if (ranks[root1] > ranks[root2]) {
            parents[root2] = root1;
        } else {
            parents[root2] = root1;
            ranks[root1]++;
        }
    }
}

std::vector<Edge> Graph::getEdges() const {
    return edges_;
}

void Graph::sortEdges(std::vector<Edge> &edges) const {
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.weight < b.weight; });
}

double Graph::generateRandomWeight() const {
    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}
