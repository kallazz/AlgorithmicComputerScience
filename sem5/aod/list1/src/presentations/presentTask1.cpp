#include "../Graph.hpp"
#include "../graphAlgorithms.hpp"

int main() {
    const Graph undirectedGraph1 = Graph(6, false, true, {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {3, 6}, {4, 5}, {5, 6}});
    const Graph directedGraph1 = Graph(6, true, true, {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {3, 6}, {4, 5}, {5, 6}});

    const Graph undirectedGraph2 = Graph(
        8, false, true, {{1, 2}, {1, 4}, {2, 3}, {2, 6}, {3, 4}, {4, 8}, {5, 1}, {5, 8}, {6, 5}, {6, 7}, {7, 3}, {8, 7}});
    const Graph directedGraph2 = Graph(
        8, true, true, {{1, 2}, {1, 4}, {2, 3}, {2, 6}, {3, 4}, {4, 8}, {5, 1}, {5, 8}, {6, 5}, {6, 7}, {7, 3}, {8, 7}});

    const Graph undirectedGraph3 = Graph(9, false, true,
                                   {{1, 2},
                                    {1, 3},
                                    {1, 5},
                                    {2, 4},
                                    {2, 5},
                                    {3, 5},
                                    {3, 6},
                                    {4, 5},
                                    {4, 8},
                                    {5, 6},
                                    {6, 7},
                                    {6, 9},
                                    {7, 4},
                                    {7, 8},
                                    {9, 7},
                                    {9, 8}});
    const Graph directedGraph3 = Graph(9, true, true,
                                 {{1, 2},
                                  {1, 3},
                                  {1, 5},
                                  {2, 4},
                                  {2, 5},
                                  {3, 5},
                                  {3, 6},
                                  {4, 5},
                                  {4, 8},
                                  {5, 6},
                                  {6, 7},
                                  {6, 9},
                                  {7, 4},
                                  {7, 8},
                                  {9, 7},
                                  {9, 8}});

    dfs(directedGraph2, 1, true);

    return 0;
}
