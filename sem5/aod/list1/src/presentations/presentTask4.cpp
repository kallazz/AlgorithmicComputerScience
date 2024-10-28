#include "../Graph.hpp"
#include "../graphAlgorithms.hpp"
#include "../graphHelpers.hpp"

#include <algorithm>
#include <iostream>

const std::string TEST_CASES_DIRECTORY = "/home/kallas/workspace/ina/sem5/aod/list1/testCases/4";
const std::string TEMPLATE_FILENAME = TEST_CASES_DIRECTORY + "/D4L-N.txt";

int main() {
    const Graph undirectedBipartiteGraph = Graph(
        10, false, true, {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}, {5, 6}, {7, 6}, {8, 7}, {9, 7}, {10, 8}, {10, 9}});
    const Graph directedBipartiteGraph = Graph(
        10, true, true, {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}, {5, 6}, {7, 6}, {8, 7}, {9, 7}, {10, 8}, {10, 9}});
    const Graph undirectedNotBipartiteGraph = Graph(
        10, false, true,
        {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}, {5, 6}, {7, 6}, {8, 7}, {9, 7}, {10, 8}, {10, 9}, {1, 4}, {10, 7}});
    const Graph directedNotBipartiteGraph = Graph(
        10, true, true,
        {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}, {5, 6}, {7, 6}, {8, 7}, {9, 7}, {10, 8}, {10, 9}, {1, 4}, {10, 7}});

    isBipartite(undirectedBipartiteGraph, true);
    std::cout << '\n';
    isBipartite(directedBipartiteGraph, true);
    std::cout << '\n';
    isBipartite(undirectedNotBipartiteGraph, true);
    std::cout << '\n';
    isBipartite(directedNotBipartiteGraph, true);
    std::cout << '\n';

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
