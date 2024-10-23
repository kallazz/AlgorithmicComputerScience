#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph {
public:
    Graph(const int numberOfVertices, const bool isDirected, const bool isIndexedFromOne);
    Graph(const int numberOfVertices, const bool isDirected, const bool isIndexedFromOne, const std::vector<std::pair<int, int>> &edges);

    void addEdge(const int vertex1, const int vertex2);
    bool isDirected() const;
    bool isIndexedFromOne() const;
    int getNumberOfVertices() const;
    const std::vector<std::vector<int>> &getAdjacencyList() const;

private:
    const int numberOfVertices_;
    const bool isDirected_;
    const bool isIndexedFromOne_;
    std::vector<std::vector<int>> adjacencyList_;
};

#endif // GRAPH_HPP