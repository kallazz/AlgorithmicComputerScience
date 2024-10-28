#include "graphAlgorithms.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

int computeTreeHeight(const int root, const std::vector<std::vector<int>> &adjacencyList) {
    if (adjacencyList[root].size() == 0) {
        return 1;
    }

    int maxHeight = 0;
    for (const int adjacentVertex : adjacencyList[root]) {
        maxHeight = std::max(maxHeight, computeTreeHeight(adjacentVertex, adjacencyList));
    }

    return maxHeight + 1;
}

void printTreeRecursive(const int node, const int depth, const std::vector<std::vector<int>> &adjacencyList,
                        std::string &trace) {
    for (int i = 0; i < depth; i++) {
        const auto currentSymbol = (trace[i] == '|') ? "|  " : "   ";
        std::cout << currentSymbol;
    }
    std::cout << "+- " << node + 1 << '\n';

    if (adjacencyList[node].size() == 0) {
        return;
    }

    for (int i = 0; i < adjacencyList[node].size(); i++) {
        trace[depth] = (i == adjacencyList[node].size() - 1) ? ' ' : '|';
        printTreeRecursive(adjacencyList[node][i], depth + 1, adjacencyList, trace);
    }
}

void printTree(const int numberOfVertices, const std::vector<std::pair<int, int>> &treeEdges) {
    Graph tree = Graph(numberOfVertices, true, false);
    for (const auto [vertex1, vertex2] : treeEdges) {
        tree.addEdge(vertex1, vertex2);
    }

    if (tree.getNumberOfEdges() > 0) {
        const int root = treeEdges[0].first;
        const int treeHeight = computeTreeHeight(root, tree.getAdjacencyList());
        std::string emptyString(treeHeight, ' ');
        printTreeRecursive(root, 0, tree.getAdjacencyList(), emptyString);
    }
}

void bfs(const Graph &graph, const int startVertex, const bool printFlag, const bool treeFlag) {
    const std::vector<std::vector<int>> &adjacencyList = graph.getAdjacencyList();
    std::vector<bool> visited(adjacencyList.size(), false);
    visited[startVertex] = true;
    std::queue<int> queue;
    queue.push(startVertex);
    std::vector<std::pair<int, int>> treeEdges;

    while (!queue.empty()) {
        const int currentVertex = queue.front();
        queue.pop();

        if (printFlag && !treeFlag) {
            std::cout << currentVertex + 1 << " ";
        }

        for (const int adjacentVertex : adjacencyList[currentVertex]) {
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                queue.push(adjacentVertex);

                treeEdges.push_back({currentVertex, adjacentVertex});
            }
        }
    }

    if (printFlag && treeFlag) {
        printTree(graph.getNumberOfVertices(), treeEdges);
    }

    if (printFlag) {
        std::cout << '\n';
    }
}

void dfs(const Graph &graph, const int startVertex, const bool printFlag, const bool treeFlag) {
    const std::vector<std::vector<int>> &adjacencyList = graph.getAdjacencyList();
    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<std::pair<int, int>> stack;
    stack.push({-1, startVertex});
    std::vector<std::pair<int, int>> treeEdges;

    while (!stack.empty()) {
        const auto [currentParent, currentVertex] = stack.top();
        stack.pop();

        if (!visited[currentVertex]) {
            visited[currentVertex] = true;

            if (printFlag && !treeFlag) {
                std::cout << currentVertex + 1 << " ";
            }

            if (currentParent != -1) {
                treeEdges.push_back({currentParent, currentVertex});
            }
        }

        for (const int adjacentVertex : adjacencyList[currentVertex]) {
            if (!visited[adjacentVertex]) {
                stack.push({currentVertex, adjacentVertex});
            }
        }
    }

    if (printFlag && treeFlag) {
        printTree(graph.getNumberOfVertices(), treeEdges);
    }

    if (printFlag) {
        std::cout << '\n';
    }
}

// Kahn's topological sort algorithm
std::optional<std::vector<int>> topologicalSort(const Graph &graph, const bool printFlag) {
    if (!graph.isDirected()) {
        return {};
    }

    const std::vector<std::vector<int>> &adjacencyList = graph.getAdjacencyList();
    std::vector<int> incomingEdgesCount(graph.getNumberOfVertices(), 0);

    for (const std::vector<int> &adjacentVertices : adjacencyList) {
        for (const int adjacentVertex : adjacentVertices) {
            incomingEdgesCount[adjacentVertex]++;
        }
    }

    std::queue<int> verticesWithNoIncomingEdges;
    for (int vertex = 0; vertex < incomingEdgesCount.size(); vertex++) {
        if (incomingEdgesCount[vertex] == 0) {
            verticesWithNoIncomingEdges.push(vertex);
        }
    }

    std::vector<int> topologicalOrder;
    while (!verticesWithNoIncomingEdges.empty()) {
        const int currentVertex = verticesWithNoIncomingEdges.front();
        verticesWithNoIncomingEdges.pop();
        topologicalOrder.push_back(currentVertex);

        for (const int adjacentVertex : adjacencyList[currentVertex]) {
            incomingEdgesCount[adjacentVertex]--;

            if (incomingEdgesCount[adjacentVertex] == 0) {
                verticesWithNoIncomingEdges.push(adjacentVertex);
            }
        }
    }

    if (topologicalOrder.size() != graph.getNumberOfVertices()) {
        if (printFlag) {
            std::cout << "Graph contains a cycle\n";
        }

        return {};
    }

    if (printFlag) {
        std::cout << "Graph does NOT contain a cycle\n";
    }

    if (printFlag && graph.getNumberOfVertices() <= 200) {
        std::cout << "Topological order: ";
        for (const int vertex : topologicalOrder) {
            std::cout << vertex + 1 << " ";
        }
        std::cout << '\n';
    }

    return topologicalOrder;
}

void strongconnect(const int vertex, int &currentIndex, std::vector<int> &index, std::vector<int> &lowLink,
                   std::vector<bool> &onStack, std::stack<int> &stack,
                   std::vector<std::vector<int>> &stronglyConnectedComponents, const Graph &graph) {
    index[vertex] = currentIndex;
    lowLink[vertex] = currentIndex;
    currentIndex++;
    stack.push(vertex);
    onStack[vertex] = true;

    for (const int adjacentVertex : graph.getAdjacencyList()[vertex]) {
        if (index[adjacentVertex] == -1) {
            strongconnect(adjacentVertex, currentIndex, index, lowLink, onStack, stack, stronglyConnectedComponents,
                          graph);
            lowLink[vertex] = std::min(lowLink[vertex], lowLink[adjacentVertex]);
        } else if (onStack[adjacentVertex]) {
            lowLink[vertex] = std::min(lowLink[vertex], lowLink[adjacentVertex]);
        }
    }

    if (lowLink[vertex] == index[vertex]) {
        int componentVertex;
        std::vector<int> component;

        do {
            componentVertex = stack.top();
            stack.pop();
            onStack[componentVertex] = false;
            component.push_back(componentVertex);
        } while (componentVertex != vertex);

        stronglyConnectedComponents.push_back(component);
    }
}

// Tarjan's strongly connected components algorithm
std::vector<std::vector<int>> getStronglyConnectedComponents(const Graph &graph) {
    std::vector<std::vector<int>> stronglyConnectedComponents;
    std::vector<int> index(graph.getNumberOfVertices(), -1);
    std::vector<int> lowLink(graph.getNumberOfVertices(), -1);
    std::vector<bool> onStack(graph.getNumberOfVertices(), false);
    std::stack<int> stack;
    int currentIndex = 0;

    for (int vertex = 0; vertex < graph.getNumberOfVertices(); vertex++) {
        if (index[vertex] == -1) {
            strongconnect(vertex, currentIndex, index, lowLink, onStack, stack, stronglyConnectedComponents, graph);
        }
    }

    return stronglyConnectedComponents;
}

bool isBipartite(const Graph &graph, const bool printFlag) {
    std::vector<int> color(graph.getNumberOfVertices(), -1);
    std::queue<int> queue;

    std::vector<std::vector<int>> adjacencyListCopy = graph.getAdjacencyList();
    if (graph.isDirected()) {
        for (int vertex = 0; vertex < graph.getNumberOfVertices(); vertex++) {
            for (const int adjacentVertex : adjacencyListCopy[vertex]) {
                if (std::find(adjacencyListCopy[adjacentVertex].begin(), adjacencyListCopy[adjacentVertex].end(),
                              vertex) == adjacencyListCopy[adjacentVertex].end()) {
                    adjacencyListCopy[adjacentVertex].push_back(vertex);
                }
            }
        }
    }

    for (int vertex = 0; vertex < graph.getNumberOfVertices(); vertex++) {
        if (color[vertex] == -1) {
            color[vertex] = 0;
            queue.push(vertex);

            while (!queue.empty()) {
                const int currentVertex = queue.front();
                queue.pop();

                for (const int adjacentVertex : adjacencyListCopy[currentVertex]) {
                    if (color[adjacentVertex] == -1) {
                        color[adjacentVertex] = 1 - color[currentVertex];
                        queue.push(adjacentVertex);
                    } else if (color[adjacentVertex] == color[currentVertex]) {
                        if (printFlag) {
                            std::cout << "Graph is NOT bipartite\n";
                        }

                        return false;
                    }
                }
            }
        }
    }

    if (printFlag) {
        std::cout << "Graph is bipartite\n";

        if (graph.getNumberOfVertices() <= 200) {
            std::cout << "First set of vertices: ";
            for (int vertex = 0; vertex < graph.getNumberOfVertices(); vertex++) {
                if (color[vertex] == 0) {
                    std::cout << vertex + 1 << " ";
                }
            }

            std::cout << "\nSecond set of vertices: ";
            for (int vertex = 0; vertex < graph.getNumberOfVertices(); vertex++) {
                if (color[vertex] == 1) {
                    std::cout << vertex + 1 << " ";
                }
            }

            std::cout << '\n';
        }
    }

    return true;
}