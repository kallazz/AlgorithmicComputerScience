#include "AlgorithmRunner.hpp"
#include "CommandLineParser.hpp"
#include "DijkstraAlgorithms.hpp"
#include "enums.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <array>
#include <map>
#include <thread>
#include <random>
#include <unordered_set>

const std::string TESTS_DIRECTORY = "../ch9-1.1/inputs/";
const std::string OUTPUT_DIRECTORY = "./output/";
const std::array<std::string, 7> FAMILY_NAMES = {"Random4-C", "Random4-n", "Long-n", "Square-n", "Long-C", "Square-C", "USA-road-t"};

const std::unordered_set<std::string> IGNORED_TESTS = {"-C.15", "-C.14", "-C.13", "fjklsajfklsaklfklajs"};
const std::unordered_set<std::string> BIGGEST_GRAPH_TESTS = {"-C.15", "-n.21", "USA-road-t.CTR"};

bool shouldTestBeIgnored(const std::string& testPath) {
    for (const auto& namePart : BIGGEST_GRAPH_TESTS ) {
        if (testPath.find(namePart) == std::string::npos) {
            return true;
        }
    }

    return false;
}

bool isOneOfTheBiggestTests(const std::string& testPath) {
    for (const auto& namePart : BIGGEST_GRAPH_TESTS) {
        if (testPath.find(namePart) != std::string::npos) {
            return true;
        }
    }

    return false;
}

std::vector<int> getRandomVertices(const int graphSize, const int numberOfVertices) {
    std::vector<int> vertices;
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, graphSize - 1);

    for (int i = 0; i < numberOfVertices; i++) {
        vertices.push_back(dist(mt));
    }

    return vertices;
}

std::pair<int, int> getRandomPair(const int graphSize) {
    int vertex1, vertex2;
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, graphSize - 1);

    vertex1 = dist(mt);
    do {
        vertex2 = dist(mt);
    } while (vertex1 == vertex2);

    return {vertex1, vertex2};
}

void handleFile(const std::filesystem::path& filePath, const bool isBiggestGraph) {
    const std::string filename = filePath.stem().string();

    std::cout << "Running the experiment for file " << filename << '\n';

    const std::string dijkstraFilenamePrefix = "Dijkstra_";
    const std::string dialFilenamePrefix = "Dial_";
    const std::string radixheapFilenamePrefix = "Radixheap_";

    const std::string dijkstraOssFilePath = OUTPUT_DIRECTORY + dijkstraFilenamePrefix + filename + ".ss.res";
    const std::string dialOssFilePath = OUTPUT_DIRECTORY + dialFilenamePrefix + filename + ".ss.res";
    const std::string radixheapOssFilePath = OUTPUT_DIRECTORY + radixheapFilenamePrefix + filename + ".ss.res";

    const Graph graph = AlgorithmRunner::createGraph(filePath);

    const std::vector<int> vertices = getRandomVertices(graph.getNumberOfVertices(), 5);

    // AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(basicDijkstra, graph, {0}, dijkstraOssFilePath);
    // AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(basicDijkstra, graph, vertices, dijkstraOssFilePath);

    // AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(dialDijkstra, graph, {0}, dialOssFilePath);
    // AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(dialDijkstra, graph, vertices, dialOssFilePath);

    // AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(radixHeapDijkstra, graph, {0}, radixheapOssFilePath);
    // AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(radixHeapDijkstra, graph, vertices, radixheapOssFilePath);

    if (isBiggestGraph) {
        std::vector<std::pair<int, int>> pairs = {{0, graph.getNumberOfVertices() - 1}};
        for (int i = 0; i < 4; i++) {
            pairs.push_back(getRandomPair(graph.getNumberOfVertices()));
        }

        const std::string dijkstraOp2pFilePath = OUTPUT_DIRECTORY + dijkstraFilenamePrefix + filename + ".p2p.res";
        // const std::string dialOp2pFilePath = OUTPUT_DIRECTORY + dialFilenamePrefix + filename + ".p2p.res";
        // const std::string radixheapOp2pFilePath = OUTPUT_DIRECTORY + radixheapFilenamePrefix + filename + ".p2p.res";

        AlgorithmRunner::runAlgorithmForPairsWithoutParsing(basicDijkstra, graph, pairs, dijkstraOp2pFilePath);
        // AlgorithmRunner::runAlgorithmForPairsWithoutParsing(dialDijkstra, graph, pairs, dialOp2pFilePath);
        // AlgorithmRunner::runAlgorithmForPairsWithoutParsing(radixHeapDijkstra, graph, pairs, radixheapOp2pFilePath);
    }          
}

void handleFamily(const std::string& familyPath, const std::string& familyName) {
    bool isBiggestGraph = false;
    for (const auto& dirEntry : std::filesystem::directory_iterator(familyPath)) {
        const std::string pathString = dirEntry.path().string();

        if (dirEntry.path().extension() == ".gr") {
            if (shouldTestBeIgnored(pathString)) {
                continue;
            }
            std::cout << dirEntry.path().string() << '\n';
            if (isOneOfTheBiggestTests(pathString)) {
                isBiggestGraph = true;
            }

            handleFile(dirEntry.path(), isBiggestGraph);

            isBiggestGraph = false;
        }
    }

    std::cout << "****************************************\n";
    std::cout << "Family " << familyName << " completed\n";
    std::cout << "****************************************\n";
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < FAMILY_NAMES.size(); i++) {
        const std::string familyPath = TESTS_DIRECTORY + FAMILY_NAMES[i] + "/";
        handleFamily(familyPath, FAMILY_NAMES[i]);
        // threads.emplace_back(handleFamily, familyPath, FAMILY_NAMES[i]);
    }

    // for (auto& thread : threads) {
    //     thread.join();
    // }

    return 0;
}
