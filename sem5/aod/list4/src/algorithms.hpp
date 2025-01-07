#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm>

class Graph;

std::pair<long long, long long> edmondsKarp(Graph& graph, const long long sourceVertex, const long long sinkVertex);

#endif // ALGORITHMS_HPP