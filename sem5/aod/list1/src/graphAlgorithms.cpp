#include "graphAlgorithms.hpp"
#include "Graph.hpp"

#include <iostream>
#include <queue>
#include <stack>

// add tree printing

void bfs(const Graph &graph, const int startVertex, const bool printFlag, const bool treeFlag) {
    const std::vector<std::vector<int>> &adjacencyList = graph.getAdjacencyList();
    std::vector<bool> visited(adjacencyList.size(), false);
    visited[startVertex] = true;
    std::queue<int> queue;
    queue.push(startVertex);
    std::vector<int> parent(adjacencyList.size(), -1);

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

                parent[adjacentVertex] = currentVertex;
            }
        }
    }

    if (printFlag && treeFlag) {
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                std::cout << parent[i] + 1 << " " << i + 1 << '\n';
            }

        }
    }

    if (printFlag) {
        std::cout << '\n';
    }
}

void dfs(const Graph &graph, const int startVertex, const bool printFlag, const bool treeFlag) {
    const std::vector<std::vector<int>> &adjacencyList = graph.getAdjacencyList();
    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<int> stack;
    stack.push(startVertex);
    std::vector<int> parent(adjacencyList.size(), -1);

    while (!stack.empty()) {
        const int currentVertex = stack.top();
        stack.pop();

        if (!visited[currentVertex]) {
            visited[currentVertex] = true;
            if (printFlag && !treeFlag) {
                std::cout << currentVertex + 1 << " ";
            }
        }

        for (const int adjacentVertex : adjacencyList[currentVertex]) {
            if (!visited[adjacentVertex]) {
                stack.push(adjacentVertex);

                parent[adjacentVertex] = currentVertex;
            }
        }
    }

    if (printFlag && treeFlag) {
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                std::cout << parent[i] + 1 << " " << i + 1 << '\n';
            }

        }
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
            lowLink[vertex] = std::min(lowLink[vertex], index[adjacentVertex]);
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
                if (std::find(adjacencyListCopy[adjacentVertex].begin(), adjacencyListCopy[adjacentVertex].end(), vertex) ==
                    adjacencyListCopy[adjacentVertex].end()) {
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