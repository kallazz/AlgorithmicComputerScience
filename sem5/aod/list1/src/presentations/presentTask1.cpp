#include "../Graph.hpp"
#include "../graphAlgorithms.hpp"
#include <iostream>

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
                                    {7, 5},
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

    const Graph myDirectedGraph = Graph(10, true, true, {{1, 2}, {2, 3}, {2, 4}, {2, 5}, {3, 6}, {4, 6}, {5, 6}, {6, 7}, {6,8 }, {6, 9}, {7, 10}, {8, 10}, {9,10}});
    const Graph myUndirectedGraph = Graph(10, false, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 1}, {2, 8}, {3, 7}});

    dfs(directedGraph1, 0, true, true);

    return 0;
}
