#include "algorithms.hpp"
#include "Graph.hpp"

#include <limits>
#include <queue>
#include <iostream>

constexpr int INF = std::numeric_limits<int>::max();

bool bfs(Graph &graph, const int sourceVertex, const int sinkVertex, std::vector<Edge*> &predecessorEdges) {
    std::queue<int> queue;
    queue.push(sourceVertex);

    while (!queue.empty()) {
        const int currentVertex = queue.front();
        queue.pop();

        for (Edge& edge : graph.getAdjacencyList()[currentVertex]) {
            if (predecessorEdges[edge.sinkVertex] == nullptr && edge.sinkVertex != sourceVertex && edge.capacity > edge.flow) {
                predecessorEdges[edge.sinkVertex] = &edge;
                queue.push(edge.sinkVertex);
            }
        }
    }

    return predecessorEdges[sinkVertex] != nullptr;
}

std::pair<int, int> edmondsKarp(Graph& graph, const int sourceVertex, const int sinkVertex) {
    int maxFlow = 0;
    int amountOfAugmentingPathsFound = 0;

    while (true) {
        std::vector<Edge*> predecessorEdges(graph.getNumberOfVertices(), nullptr);
        if (!bfs(graph, sourceVertex, sinkVertex, predecessorEdges)) {
            return {maxFlow, amountOfAugmentingPathsFound};
        }

        amountOfAugmentingPathsFound++;

        int pathFlow = INF;
        for (Edge* edge = predecessorEdges[sinkVertex]; edge != nullptr; edge = predecessorEdges[edge->sourceVertex]) {
            pathFlow = std::min(pathFlow, edge->capacity - edge->flow);
        }
        for (Edge* edge = predecessorEdges[sinkVertex]; edge != nullptr; edge = predecessorEdges[edge->sourceVertex]) {
            edge->flow += pathFlow;
            auto& reverseEdge = graph.getAdjacencyList()[edge->sinkVertex][edge->reverseEdgeIndex];
            reverseEdge.flow -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return {maxFlow, amountOfAugmentingPathsFound};
}
