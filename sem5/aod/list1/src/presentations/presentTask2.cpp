#include "../Graph.hpp"
#include "../graphAlgorithms.hpp"
#include "../graphHelpers.hpp"

#include <iostream>

const std::string TEST_CASES_DIRECTORY = "/home/kallas/workspace/ina/sem5/aod/list1/testCases/2";
const std::string TEMPLATE_FILENAME = TEST_CASES_DIRECTORY + "/g2L-N.txt";

int main() {
    const Graph directedAcyclicGraph = Graph(10, true, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}});
    const Graph directedCyclicGraph = Graph(10, true, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 1}});

    const Graph graphFromWiki = Graph(11, true, true, {{3, 8}, {3, 10}, {5, 11}, {7, 8}, {7, 11}, {8, 9}, {11, 2}, {11, 9}, {11, 10}});

    topologicalSort(graphFromWiki, true);


    for (const auto letter : {'a', 'b'}) {
        for (int number = 1; number <= 6; number++) {
            std::string currentFilename = TEMPLATE_FILENAME;
            std::replace(currentFilename.begin(), currentFilename.end(), 'L', letter);
            std::replace(currentFilename.begin(), currentFilename.end(), 'N', char('0' + number));

            const Graph currentGraph = createGraphFromFilename(currentFilename);

            std::cout << "Topological sort for " << currentFilename << ":\n";
            topologicalSort(currentGraph, true);
        }
    }

    return 0;
}
