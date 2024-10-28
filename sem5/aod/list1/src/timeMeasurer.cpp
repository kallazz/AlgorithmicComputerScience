#include "Graph.hpp"
#include "graphAlgorithms.hpp"
#include "graphHelpers.hpp"

#include <array>
#include <chrono>
#include <fstream>
#include <iostream>

// Stack size needs to be increased for the largest test case from task 3
// ulimit -s unlimited

const std::string TEST_CASES_DIRECTORY = "/home/kallas/workspace/ina/sem5/aod/list1/testCases/";
const std::string RESULTS_DIRECTORY = "/home/kallas/workspace/ina/sem5/aod/list1/timeResults/";

int main() {
    std::ofstream task1File(RESULTS_DIRECTORY + "task1Times.txt");
    std::ofstream task2File(RESULTS_DIRECTORY + "task2Times.txt");
    std::ofstream task3File(RESULTS_DIRECTORY + "task3Times.txt");
    std::ofstream task4File(RESULTS_DIRECTORY + "task4Times.txt");

    const std::array task2Filenames = {
        "g2a-1.txt", "g2a-2.txt", "g2a-3.txt", "g2a-4.txt", "g2a-5.txt", "g2a-6.txt",
        "g2b-1.txt", "g2b-2.txt", "g2b-3.txt", "g2b-4.txt", "g2b-5.txt", "g2b-6.txt",
    };

    const std::array task3Filenames = {
        "g3-1.txt", "g3-2.txt", "g3-3.txt", "g3-4.txt", "g3-5.txt", "g3-6.txt",
    };

    const std::array task4Filenames = {
        "d4a-1.txt", "d4a-2.txt", "d4a-3.txt", "d4a-4.txt", "d4a-5.txt", "d4a-6.txt", "d4b-1.txt", "d4b-2.txt",
        "d4b-3.txt", "d4b-4.txt", "d4b-5.txt", "d4b-6.txt", "u4a-1.txt", "u4a-2.txt", "u4a-3.txt", "u4a-4.txt",
        "u4a-5.txt", "u4a-6.txt", "u4b-1.txt", "u4b-2.txt", "u4b-3.txt", "u4b-4.txt", "u4b-5.txt", "u4b-6.txt",
    };

    const Graph task1UndirectedGraph1 =
        Graph(6, false, true, {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {3, 6}, {4, 5}, {5, 6}});
    const Graph task1DirectedGraph1 =
        Graph(6, true, true, {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {3, 6}, {4, 5}, {5, 6}});

    const Graph task1UndirectedGraph2 =
        Graph(8, false, true,
              {{1, 2}, {1, 4}, {2, 3}, {2, 6}, {3, 4}, {4, 8}, {5, 1}, {5, 8}, {6, 5}, {6, 7}, {7, 3}, {8, 7}});
    const Graph task1DirectedGraph2 =
        Graph(8, true, true,
              {{1, 2}, {1, 4}, {2, 3}, {2, 6}, {3, 4}, {4, 8}, {5, 1}, {5, 8}, {6, 5}, {6, 7}, {7, 3}, {8, 7}});

    const Graph task1UndirectedGraph3 = Graph(9, false, true,
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
    const Graph task1DirectedGraph3 = Graph(9, true, true,
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

    const Graph task1MyUnDirectedGraph =
        Graph(10, false, true,
              {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 1}, {2, 8}, {3, 7}});
    const Graph task1MyDirectedGraph =
        Graph(10, true, true,
              {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 1}, {2, 8}, {3, 7}});

    for (const auto &currentGraph :
         {task1UndirectedGraph1, task1UndirectedGraph2, task1UndirectedGraph3, task1MyUnDirectedGraph,
          task1DirectedGraph1, task1DirectedGraph2, task1DirectedGraph3, task1MyDirectedGraph}) {
        const auto bfsStartTime = std::chrono::high_resolution_clock::now();
        bfs(currentGraph, false, false);
        const auto bfsEndTime = std::chrono::high_resolution_clock::now();

        const auto dfsStartTime = std::chrono::high_resolution_clock::now();
        dfs(currentGraph, false, false);
        const auto dfsEndTime = std::chrono::high_resolution_clock::now();

        const auto bfsDuration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(bfsEndTime - bfsStartTime).count();
        const auto dfsDuration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(dfsEndTime - dfsStartTime).count();

        task1File << currentGraph.isDirected() << " " << currentGraph.getNumberOfVertices() << " "
                  << currentGraph.getNumberOfEdges() << " " << bfsDuration << " " << dfsDuration << '\n';
    }

    for (const auto &filename : task2Filenames) {
        const std::string currentFilename = TEST_CASES_DIRECTORY + "2/" + filename;
        const Graph currentGraph = createGraphFromFilename(currentFilename);

        const auto startTime = std::chrono::high_resolution_clock::now();
        topologicalSort(currentGraph, false);
        const auto endTime = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        task2File << filename << " " << currentGraph.isDirected() << " " << currentGraph.getNumberOfVertices() << " "
                  << currentGraph.getNumberOfEdges() << " " << duration << '\n';
    }

    for (const auto &filename : task3Filenames) {
        const std::string currentFilename = TEST_CASES_DIRECTORY + "3/" + filename;
        const Graph currentGraph = createGraphFromFilename(currentFilename);

        const auto startTime = std::chrono::high_resolution_clock::now();
        getStronglyConnectedComponents(currentGraph);
        const auto endTime = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        task3File << filename << " " << currentGraph.isDirected() << " " << currentGraph.getNumberOfVertices() << " "
                  << currentGraph.getNumberOfEdges() << " " << duration << '\n';
    }

    for (const auto &filename : task4Filenames) {
        const std::string currentFilename = TEST_CASES_DIRECTORY + "4/" + filename;
        const Graph currentGraph = createGraphFromFilename(currentFilename);

        const auto startTime = std::chrono::high_resolution_clock::now();
        isBipartite(currentGraph, false);
        const auto endTime = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        task4File << filename << " " << currentGraph.isDirected() << " " << currentGraph.getNumberOfVertices() << " "
                  << currentGraph.getNumberOfEdges() << " " << duration << '\n';
    }

    return 0;
}
