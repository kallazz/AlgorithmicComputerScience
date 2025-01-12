#include <chrono>
#include <iostream>
#include <fstream>

#include "algorithms.hpp"
#include "Graph.hpp"

const std::string OUTPUT_DIRECTORY = "./models/";

void generateLinearProgrammingModel(Graph &graph, const std::string &outputFilePath) {
    std::ofstream outputFile(outputFilePath);

    outputFile << "using GLPK\n";
    outputFile << "using JuMP\n\n";

    outputFile << "size = " << graph.getNumberOfVertices() << "\n";
    outputFile << "graph_matrix = [\n";
    for (int vertex = 0; vertex < graph.getNumberOfVertices(); vertex++) {
        std::vector<int> matrixRow(graph.getNumberOfVertices());
        for (const auto& edge : graph.getAdjacencyList()[vertex]) {
            matrixRow[edge.sinkVertex] = edge.capacity;
        }

        outputFile << "    ";
        for (int i = 0; i < graph.getNumberOfVertices() - 1; i++) {
            outputFile << matrixRow[i] << " ";
        }
        outputFile << matrixRow[graph.getNumberOfVertices() - 1] << ";\n";
    }
    outputFile << "]\n\n";
    
    outputFile << "model = Model(GLPK.Optimizer)\n\n";

    outputFile << "# Define variable for holding flows\n";
    outputFile << "@variable(model, f[1:size, 1:size] >= 0)\n\n";

    outputFile << "# Flows need to be less than or equal to capacities\n";
    outputFile << "@constraint(model, [i=1:size, j=1:size], f[i, j] <= graph_matrix[i, j])\n\n";

    outputFile << "# Flow needs to be balanced\n";
    outputFile << "@constraint(model, [i=2:size-1], sum(f[i, :]) == sum(f[:, i]))\n\n";

    outputFile << "# The objective is maximizing the flow\n";
    outputFile << "@objective(model, Max, sum(f[1, :]))\n";
    outputFile << "optimize!(model)\n\n";

    outputFile << "println(\"Max Flow: $(objective_value(model))\")\n";
    outputFile << "println(\"Solve Time: $(solve_time(model))\")\n";

    outputFile.close();
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cout << "Problem's name needs to be provided as the first argument(flow/matching)";
        return 1;
    }

    std::string chosenProblem = argv[1];

    if (chosenProblem == "flow") {
        bool wasGlpkFlagProvided = false;
        bool wasSizeProvided = false;
        bool wasPrintFlowFlagProvided = false;
        int size;
        std::string modelFileName;

        if (argc < 4) {
            std::cout << "Not enough arguments provided\n";
            return 1;
        }
        if (argc > 7) {
            std::cout << "Too many arguments provided\n";
            return 1;
        }

        for (int i = 2; i < argc; i++) {
            if (std::string(argv[i]) == "--glpk" && i + 1 < argc) {
                wasGlpkFlagProvided = true;
                modelFileName = argv[i + 1];
                i++;
            }

            if (std::string(argv[i]) == "--size" && i + 1 < argc) {
                wasSizeProvided = true;
                size = std::stoi(argv[i + 1]);
                i++;
            }

            if (std::string(argv[i]) == "--printFlow") {
                wasPrintFlowFlagProvided = true;
            } 
        }

        if (!wasSizeProvided) {
            std::cout << "Size was not provided\n";
            return 1;
        }

        Graph hypercube = Graph::createHypercube(size);
        const int sourceVertex = 0;
        const int sinkVertex = (1 << size) - 1;

        if (wasGlpkFlagProvided) {
            generateLinearProgrammingModel(hypercube, OUTPUT_DIRECTORY + modelFileName);
        }

        const auto startTime = std::chrono::high_resolution_clock::now();
        const auto [maxFlow, amountOfAugmentingPathsFound] = edmondsKarp(hypercube, sourceVertex, sinkVertex);
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

        std::cout << "Max flow: " << maxFlow << "\n";

        if (wasPrintFlowFlagProvided) {
            for (const auto &edges: hypercube.getAdjacencyList()) {
                for (const auto &edge : edges) {
                    std::cout << edge.sourceVertex << "->" << edge.sinkVertex << ": " << edge.flow << '\n';
                }
            }
        }

        std::cerr << duration.count() / 1000000 << "ms " << amountOfAugmentingPathsFound << "\n";

    } else if (chosenProblem == "matching") {
        bool wasGlpkFlagProvided = false;
        bool wasSizeProvided = false;
        bool wasDegreeProvided = false;
        bool wasPrintMatchingFlagProvided = false;
        int size;
        int degree;
        std::string modelFileName;

        if (argc < 6) {
            std::cout << "Not enough arguments provided\n";
            return 1;
        }
        if (argc > 9) {
            std::cout << "Too many arguments provided\n";
            return 1;
        }

        for (int i = 2; i < argc; i++) {
            if (std::string(argv[i]) == "--glpk" && i + 1 < argc) {
                wasGlpkFlagProvided = true;
                modelFileName = argv[i + 1];
                i++;
            }

            if (argv[i] == std::string("--size") && i + 1 < argc) {
                wasSizeProvided = true;
                size = std::stoi(argv[i + 1]);
                i++;
            }

            if (argv[i] == std::string("--degree") && i + 1 < argc) {
                wasDegreeProvided = true;
                degree = std::stoi(argv[i + 1]);
                i++;
            }

            if (argv[i] == std::string("--printMatching")) {
                wasPrintMatchingFlagProvided = true;
            } 
        }

        if (!wasSizeProvided) {
            std::cout << "Size was not provided\n";
            return 1;
        }
        if (!wasDegreeProvided) {
            std::cout << "Degree was not provided\n";
            return 1;
        }

        Graph bipartiteGraph = Graph::createBipartiteGraph(size, degree);
        const int sourceVertex = 1 << (size + 1);
        const int sinkVertex = sourceVertex + 1;

        if (wasGlpkFlagProvided) {
            generateLinearProgrammingModel(bipartiteGraph, OUTPUT_DIRECTORY + modelFileName);
        }

        const auto startTime = std::chrono::high_resolution_clock::now();
        const auto [maxMatchingSize, _] = edmondsKarp(bipartiteGraph, sourceVertex, sinkVertex);
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

        std::cout << "Max Matching Size: " << maxMatchingSize << "\n";

        if (wasPrintMatchingFlagProvided) {
            for (const auto &edges: bipartiteGraph.getAdjacencyList()) {
                for (const auto &edge : edges) {
                    std::cout << edge.sourceVertex << "->" << edge.sinkVertex << ": " << edge.flow << '\n';
                }
            }
        }

        std::cerr << duration.count() / 1000000 << "ms\n";

    } else {
        std::cout << chosenProblem << " is not any of the possible options\n";
        return 1;
    }

    return 0;
}
