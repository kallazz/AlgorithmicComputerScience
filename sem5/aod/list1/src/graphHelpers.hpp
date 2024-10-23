#ifndef GRAPH_HELPERS_HPP
#define GRAPH_HELPERS_HPP

#include <string>
#include <vector>

class Graph;

Graph createGraphFromFilename(const std::string &filename);
void printStronglyConnectedComponents(const std::vector<std::vector<int>> &stronglyConnectedComponents, const int numberOfVertices);

#endif // GRAPH_HELPERS_HPP