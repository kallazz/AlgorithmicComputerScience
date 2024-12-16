#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph {
public:
    Graph(const int numberOfVertices, const bool isDirected);
    Graph(const int numberOfVertices, const bool isDirected, const std::vector<std::tuple<int, int, int>> &edges);

    void addEdge(const int vertex1, const int vertex2, int weight);
    bool isDirected() const;
    int getNumberOfVertices() const;
    int getNumberOfEdges() const;
    int getMaxWeight() const;
    const std::vector<std::vector<std::pair<int, int>>> &getAdjacencyList() const;

private:
    const int numberOfVertices_;
    int numberOfEdges_;
    const bool isDirected_;
    int maxWeight_;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList_;
};

#endif // GRAPH_HPP