#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    int node1;
    int node2;
    double weight;

    Edge(const int node1, const int node2, const double weight) : node1(node1), node2(node2), weight(weight) {}
};

class Graph {
public:
    Graph(const int size);

    static Graph generateRandomCompleteGraph(const int size);

    void addWeightedEdge(const int node1, const int node2, const double weight);
    void addRandomWeightedEdge(const int node1, const int node2);

    Graph generateKruskalsMinimumSpanningTree() const;
    Graph generatePrimsMinimumSpanningTree() const;

    std::vector<std::vector<double>> getAdjecencyMatrix() const;
    std::vector<Edge> getEdges() const;

    std::pair<std::vector<std::vector<int>>, std::vector<int>> findShortestInfoSpreadOrder(const int startNode) const;

private:
    const int UNCONNECTED_WEIGHT_{-1};
    int size_;
    std::vector<std::vector<double>> adjacencyMatrix_;
    std::vector<Edge> edges_;

    int find(const int node, std::vector<int> &parents) const;
    void unite(const int node1, const int node2, std::vector<int> &parents, std::vector<int> &ranks) const;
    void sortEdges(std::vector<Edge> &edges) const;

    int findMinNode(const std::vector<double> &costs, const std::vector<bool> &visited) const;

    double generateRandomWeight() const;

    std::vector<std::vector<int>> createChildrenLists(const int startNode) const;
    void findShortestInfoSpreadOrder(const int startNode, const std::vector<std::vector<int>> &childrenLists,
                                     std::vector<std::vector<int>> &order, std::vector<int> &roundsLeft) const;
    bool isLeaf(const int node, const std::vector<std::vector<int>> &childrenLists) const;
};

#endif  // GRAPH_HPP
