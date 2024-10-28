#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

class Graph;

#include <vector>
#include <optional>

void bfs(const Graph& graph, const int startVertex, const bool printFlag = false, const bool treeFlag = false);
void dfs(const Graph& graph, const int startVertex, const bool printFlag = false, const bool treeFlag = false);
std::optional<std::vector<int>> topologicalSort(const Graph& graph, const bool printFlag = false);
std::vector<std::vector<int>> getStronglyConnectedComponents(const Graph& graph);
bool isBipartite(const Graph& graph, const bool printFlag = false);

#endif // SEARCH_ALGORITHMS_HPP