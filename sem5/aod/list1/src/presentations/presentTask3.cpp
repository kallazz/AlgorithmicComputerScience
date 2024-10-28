#include "../Graph.hpp"
#include "../graphAlgorithms.hpp"
#include "../graphHelpers.hpp"

#include <iostream>

// Stack size needs to be increased for the largest test case
// ulimit -s unlimited

const std::string TEST_CASES_DIRECTORY = "/home/kallas/workspace/ina/sem5/aod/list1/testCases/3";
const std::string TEMPLATE_FILENAME = TEST_CASES_DIRECTORY + "/g3-N.txt";

int main() {
    const Graph graphWithOneStronglyConnectedComponent =
        Graph(10, true, true, {{1, 2}, {2, 3}, {3, 4}, {3, 1}, {3, 10}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 2}, {9, 1}, {9, 10}, {10, 2}});
    const Graph graphWithFourStronglyConnectedComponents =
        Graph(11, true, true, {{1, 2}, {1, 3}, {2, 5}, {2, 6}, {3, 4}, {3, 6}, {4, 1}, {5, 1}, {6, 7}, {7, 8}, {7, 9}, {8, 7}, {9, 10}, {10, 11}, {11, 9}});

    std::cout << "Graph with one strongly connected component:\n";
    auto stronglyConnectedComponents = getStronglyConnectedComponents(graphWithOneStronglyConnectedComponent);
    printStronglyConnectedComponents(stronglyConnectedComponents,
                                     graphWithOneStronglyConnectedComponent.getNumberOfVertices());

    std::cout << "\nGraph with four strongly connected components:\n";
    stronglyConnectedComponents = getStronglyConnectedComponents(graphWithFourStronglyConnectedComponents);
    printStronglyConnectedComponents(stronglyConnectedComponents,
                                     graphWithFourStronglyConnectedComponents.getNumberOfVertices());

    for (int number = 1; number <= 6; number++) {
        std::string currentFilename = TEMPLATE_FILENAME;
        std::replace(currentFilename.begin(), currentFilename.end(), 'N', char('0' + number));

        const Graph currentGraph = createGraphFromFilename(currentFilename);
        stronglyConnectedComponents = getStronglyConnectedComponents(currentGraph);

        std::cout << currentFilename << ":\n";
        printStronglyConnectedComponents(stronglyConnectedComponents, currentGraph.getNumberOfVertices());
    }

    return 0;
}
