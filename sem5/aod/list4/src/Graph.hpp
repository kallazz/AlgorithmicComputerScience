#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    long long sourceVertex;
    long long sinkVertex;
    long long capacity;
    long long flow;
    long long reverseEdgeIndex;

    Edge(const long long sourceVertex, const long long sinkVertex) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(0), flow(0), reverseEdgeIndex(-1) {}
    Edge(const long long sourceVertex, const long long sinkVertex, const long long capacity) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(capacity), flow(0), reverseEdgeIndex(-1) {}
    Edge(const long long sourceVertex, const long long sinkVertex, const long long capacity, const long long flow) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(capacity), flow(flow), reverseEdgeIndex(-1) {}
    Edge(const long long sourceVertex, const long long sinkVertex, const long long capacity, const long long flow, const long long reverseEdgeIndex) : sourceVertex(sourceVertex), sinkVertex(sinkVertex), capacity(capacity), flow(flow), reverseEdgeIndex(reverseEdgeIndex) {}
};

class Graph {
public:
    Graph(const long long numberOfVertices, const bool isDirected);

    static Graph createHypercube(const long long size);

    void addEdge(const long long vertex1, const long long vertex2, const long long capacity);
    bool isDirected() const;
    long long getNumberOfVertices() const;
    long long getNumberOfEdges() const;
    std::vector<std::vector<Edge>> &getAdjacencyList();


private:
    const long long numberOfVertices_;
    long long numberOfEdges_;
    const bool isDirected_;
    std::vector<std::vector<Edge>> adjacencyList_;
};

#endif // GRAPH_HPP