#include "Graph.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <random>

Graph::Graph(const int size)
    : size_(size),
      adjacencyMatrix_(std::vector<std::vector<double>>(size, std::vector<double>(size, UNCONNECTED_WEIGHT_))) {}

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
    adjacencyMatrix_[node1][node2] = weight;
    adjacencyMatrix_[node2][node1] = weight;
}

void Graph::addRandomWeightedEdge(const int node1, const int node2) {
    addWeightedEdge(node1, node2, generateRandomWeight());
}

double Graph::generateRandomWeight() const {
    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

Graph Graph::generateKruskalsMinimumSpanningTree() const {
    std::vector<int> previous;
    std::vector<int> ranks;
    for (int i = 0; i < size_; i++) {
        previous.push_back(i);
        ranks.push_back(0);
    }

    std::vector<Edge> edges = edges_;
    sortEdges(edges);

    Graph minimumSpanningTree(size_);
    for (const Edge &edge : edges) {
        if (find(edge.node1, previous) != find(edge.node2, previous)) {
            minimumSpanningTree.addWeightedEdge(edge.node1, edge.node2, edge.weight);
            unite(edge.node1, edge.node2, previous, ranks);
        }
    }

    return minimumSpanningTree;
}

int Graph::find(const int node, std::vector<int> &previous) const {
    if (previous[node] != node) {
        previous[node] = find(previous[node], previous);
    }

    return previous[node];
}

void Graph::unite(const int node1, const int node2, std::vector<int> &previous, std::vector<int> &ranks) const {
    const int root1 = find(node1, previous);
    const int root2 = find(node2, previous);

    if (root1 != root2) {
        if (ranks[root1] < ranks[root2]) {
            previous[root1] = root2;
        } else if (ranks[root1] > ranks[root2]) {
            previous[root2] = root1;
        } else {
            previous[root2] = root1;
            ranks[root1]++;
        }
    }
}

void Graph::sortEdges(std::vector<Edge> &edges) const {
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.weight < b.weight; });
}

Graph Graph::generatePrimsMinimumSpanningTree() const {
    std::vector<bool> visited(size_, false);
    std::vector<double> cost(size_, std::numeric_limits<double>::max());
    std::vector<int> previous(size_, -1);

    cost[0] = 0;

    for (int i = 0; i < size_ - 1; i++) {
        const int minNode = findMinNode(cost, visited);
        visited[minNode] = true;

        for (int neighbourNode = 0; neighbourNode < size_; neighbourNode++) {
            if (!visited[neighbourNode] && adjacencyMatrix_[minNode][neighbourNode] != UNCONNECTED_WEIGHT_ &&
                adjacencyMatrix_[minNode][neighbourNode] < cost[neighbourNode]) {
                cost[neighbourNode] = adjacencyMatrix_[minNode][neighbourNode];
                previous[neighbourNode] = minNode;
            }
        }
    }

    Graph minimumSpanningTree(size_);
    for (int i = 1; i < size_; i++) {
        minimumSpanningTree.addWeightedEdge(previous[i], i, adjacencyMatrix_[i][previous[i]]);
    }

    return minimumSpanningTree;
}

int Graph::findMinNode(const std::vector<double> &cost, const std::vector<bool> &visited) const {
    double minValue = std::numeric_limits<double>::max();
    int minIndex = -1;

    for (int node = 0; node < size_; node++) {
        if (!visited[node] && cost[node] < minValue) {
            minValue = cost[node];
            minIndex = node;
        }
    }

    return minIndex;
}

std::vector<std::vector<double>> Graph::getAdjecencyMatrix() const {
    return adjacencyMatrix_;
}

std::vector<Edge> Graph::getEdges() const {
    return edges_;
}

std::pair<std::vector<int>, int> Graph::findShortestInfoSpreadOrder(const int startNode) const {
    std::vector<std::vector<int>> adjacencyList = createAdjacencyList();
    std::vector<int> nodeRoundNumbers(size_, -1);
    std::queue<int> nodesToVisit;

    nodesToVisit.push(startNode);
    nodeRoundNumbers[startNode] = 0;
    int finalRoundNumber = 0;

    while (!nodesToVisit.empty()) {
        for (int i = 0; i < nodesToVisit.size(); i++) {
            const int currentNode = nodesToVisit.front();
            nodesToVisit.pop();

            std::vector<int> unvisitedNeighbours;
            for (const int neighbour : adjacencyList[currentNode]) {
                if (nodeRoundNumbers[neighbour] == -1) {
                    unvisitedNeighbours.push_back(neighbour);
                }
            }
            std::sort(unvisitedNeighbours.begin(), unvisitedNeighbours.end(),
                      [&](const int a, const int b) { return adjacencyList[a].size() > adjacencyList[b].size(); });
            int currentRoundNumber = nodeRoundNumbers[currentNode] + 1;

            for (const int neighbour : unvisitedNeighbours) {
                if (nodeRoundNumbers[neighbour] == -1) {
                    nodeRoundNumbers[neighbour] = currentRoundNumber;
                    finalRoundNumber = std::max(finalRoundNumber, currentRoundNumber);
                    nodesToVisit.push(neighbour);
                    currentRoundNumber++;
                }
            }
        }
    }

    return std::make_pair(nodeRoundNumbers, finalRoundNumber);
}

std::vector<std::vector<int>> Graph::createAdjacencyList() const {
    std::vector<std::vector<int>> adjacencyList(size_);

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (adjacencyMatrix_[i][j] != UNCONNECTED_WEIGHT_) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    return adjacencyList;
}
