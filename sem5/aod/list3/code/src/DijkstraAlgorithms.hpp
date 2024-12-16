#ifndef DIJKSTRA_ALGORITHMS_HPP
#define DIJKSTRA_ALGORITHMS_HPP

#include <vector>

class Graph;

std::vector<long long> basicDijkstra(const Graph &graph, const int sourceVertex);
std::vector<long long> dialDijkstra(const Graph &graph, const int sourceVertex);
std::vector<long long> radixHeapDijkstra(const Graph &graph, const int sourceVertex);

#endif // DIJKSTRA_ALGORITHMS_HPP