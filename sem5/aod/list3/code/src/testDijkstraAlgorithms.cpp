#include "Graph.hpp"
#include "DijkstraAlgorithms.hpp"

#include "assert.h"
#include <iostream>

void assertDistances(const std::vector<long long> distances)
{
    assert(distances[1] == 4);
    assert(distances[2] == 12);
    assert(distances[3] == 19);
    assert(distances[4] == 21);
    assert(distances[5] == 11);
    assert(distances[6] == 9);
    assert(distances[7] == 8);
    assert(distances[8] == 14);
}

int main()
{
    const Graph graph = Graph(9, false,
                              {{0, 1, 4}, {0, 7, 8}, {1, 7, 11}, {1, 2, 8}, {2, 3, 7}, {2, 5, 4}, {2, 8, 2}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7}});

    const auto basicDistances = basicDijkstra(graph, 0);
    const auto dialDistances = dialDijkstra(graph, 0);
    const auto radixHeapDistances = radixHeapDijkstra(graph, 0);

    assertDistances(basicDistances);
    std::cout << "Assertions passed for basic Dijkstra's algorithm.\n";
    assertDistances(dialDistances);
    std::cout << "Assertions passed for Dial's Dijkstra's algorithm.\n";
    assertDistances(radixHeapDistances);
    std::cout << "Assertions passed for Radix Heap Dijkstra's algorithm.\n";
}
