#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    const int node1;
    const int node2;
    double weight;

    Edge(const int node1, const int node2, const double weight) : node1(node1), node2(node2), weight(weight) {} 
};

// void sortEdges(std::vector<Edge> &edges) const;

class Graph {
public:
    Graph(const int size);

    static Graph generateRandomCompleteGraph(const int size);

    void addWeightedEdge(const int node1, const int node2, const double weight);
    void addRandomWeightedEdge(const int node1, const int node2);
    std::vector<Edge> getEdges() const;
    Graph getKruskalsMinimumSpanningTree() const;
    Graph getPrimsMinimumSpanningTree() const;
private:
    const int size_;
    std::vector<Edge> edges_;

    void sortEdges(std::vector<Edge> &edges) const;
    double generateRandomWeight() const;
};

#endif // GRAPH_HPP