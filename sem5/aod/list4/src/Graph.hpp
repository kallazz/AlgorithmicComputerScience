#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    int sourceVertex;
    int sinkVertex;
    int capacity;
    int flow;
    int reverseEdgeIndex;

    Edge(const int sourceVertex, const int sinkVertex) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(0), flow(0), reverseEdgeIndex(-1) {}
    Edge(const int sourceVertex, const int sinkVertex, const int capacity) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(capacity), flow(0), reverseEdgeIndex(-1) {}
    Edge(const int sourceVertex, const int sinkVertex, const int capacity, const int flow) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(capacity), flow(flow), reverseEdgeIndex(-1) {}
    Edge(const int sourceVertex, const int sinkVertex, const int capacity, const int flow, const int reverseEdgeIndex) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(capacity), flow(flow), reverseEdgeIndex(reverseEdgeIndex) {}
};

class Graph {
public:
    Graph(const int numberOfVertices);

    static Graph createHypercube(const int size);
    static Graph createBipartiteGraph(const int size, const int vertexDegree);

    void addEdge(const int vertex1, const int vertex2, const int capacity);
    int getNumberOfVertices() const;
    std::vector<std::vector<Edge>> &getAdjacencyList();


private:
    const int numberOfVertices_;
    std::vector<std::vector<Edge>> adjacencyList_;
};

#endif // GRAPH_HPP