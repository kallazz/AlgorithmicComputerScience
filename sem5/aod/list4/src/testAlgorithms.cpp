#include "algorithms.hpp"
#include "Graph.hpp"

#include <assert.h>
#include <iostream>

void testEdmondsKarp() {
    Graph graph1 = Graph(6);
    graph1.addEdge(0, 1, 3);
    graph1.addEdge(0, 2, 7);
    graph1.addEdge(1, 3, 3);
    graph1.addEdge(1, 4, 4);
    graph1.addEdge(2, 1, 5);
    graph1.addEdge(2, 4, 3);
    graph1.addEdge(3, 4, 3);
    graph1.addEdge(3, 5, 2);
    graph1.addEdge(4, 5, 6);

    const auto [maxFlow1, _] = edmondsKarp(graph1, 0, 5);
    assert(maxFlow1 == 8);

    Graph graph2 = Graph(8);
    graph2.addEdge(0,1,1);
    graph2.addEdge(1,2,1);
    graph2.addEdge(2,4,1);
    graph2.addEdge(0,3,1);
    graph2.addEdge(3,4,1);
    graph2.addEdge(4,7,1);
    graph2.addEdge(3,5,1);
    graph2.addEdge(5,6,1);
    graph2.addEdge(6,7,1);

    const auto [maxFlow2, __] = edmondsKarp(graph2, 0, 7);
    assert(maxFlow2 == 2);

}

int main() {
    testEdmondsKarp();

    std::cout << "All tests passed!\n";

    return 0;
}
