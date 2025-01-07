#include "algorithms.hpp"
#include "Graph.hpp"

#include <limits>
#include <queue>
#include <iostream>

constexpr long long INF = std::numeric_limits<long long>::max();

bool bfs(Graph &graph, const long long sourceVertex, const long long sinkVertex, std::vector<Edge*> &predecessorEdges) {
    std::queue<long long> queue;
    queue.push(sourceVertex);

    while (!queue.empty()) {
        const long long currentVertex = queue.front();
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

std::pair<long long, long long> edmondsKarp(Graph& graph, const long long sourceVertex, const long long sinkVertex) {
    long long maxFlow = 0;
    long long amountOfAugmentingPathsFound = 0;

    while (true) {
        std::vector<Edge*> predecessorEdges(graph.getNumberOfVertices(), nullptr);
        if (!bfs(graph, sourceVertex, sinkVertex, predecessorEdges)) {
            return {maxFlow, amountOfAugmentingPathsFound};
        }

        amountOfAugmentingPathsFound++;

        long long pathFlow = INF;
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
