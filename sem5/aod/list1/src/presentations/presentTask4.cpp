#include "../Graph.hpp"
#include "../graphAlgorithms.hpp"
#include "../graphHelpers.hpp"

#include <iostream>

const std::string TEST_CASES_DIRECTORY = "/home/kallas/workspace/ina/sem5/aod/list1/testCases/4";
const std::string TEMPLATE_FILENAME = TEST_CASES_DIRECTORY + "/D4L-N.txt";

int main() {
    const Graph undirectedNotBipartiteGraph = Graph(
        11, false, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 1}});
    const Graph directedNotBipartiteGraph = Graph(
        11, true, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 1}});
    const Graph undirectedBipartiteGraph =
        Graph(11, false, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}});
    const Graph directedBipartiteGraph =
        Graph(11, true, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}});

    isBipartite(undirectedNotBipartiteGraph, true);
    isBipartite(directedNotBipartiteGraph, true);
    isBipartite(undirectedBipartiteGraph, true);
    isBipartite(directedBipartiteGraph, true);

    for (const char directionality : {'d', 'u'}) {
        for (const char letter : {'a', 'b'}) {
            for (int number = 1; number <= 6; number++) {
                std::string currentFilename = TEMPLATE_FILENAME;
                std::replace(currentFilename.begin(), currentFilename.end(), 'D', directionality);
                std::replace(currentFilename.begin(), currentFilename.end(), 'L', letter);
                std::replace(currentFilename.begin(), currentFilename.end(), 'N', char('0' + number));

                const Graph currentGraph = createGraphFromFilename(currentFilename);

                std::cout << currentFilename << ":\n";
                isBipartite(currentGraph, true);
            }
        }
    }

    return 0;
}
