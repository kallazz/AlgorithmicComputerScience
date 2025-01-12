#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm>

class Graph;

std::pair<int, int> edmondsKarp(Graph& graph, const int sourceVertex, const int sinkVertex);

#endif // ALGORITHMS_HPP