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
        Graph(10, true, true, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 1}});
    const Graph graphWithFourStronglyConnectedComponents =
        Graph(10, true, true, {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}, {6, 4}, {7, 8}, {8, 9}, {9, 7}});

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
