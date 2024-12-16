#include "AlgorithmRunner.hpp"
#include "DijkstraAlgorithms.hpp"

#include <fstream>
#include <sstream>
#include <optional>
#include <unordered_map>
#include <chrono>

const std::unordered_map<AlgorithmType, std::function<std::vector<long long>(const Graph&, const int)>> ALGORITHM_TYPE_TO_FUNCTION = {
    {DIJKSTRA, basicDijkstra},
    {DIAL, dialDijkstra},
    {RADIXHEAP, radixHeapDijkstra}
};

AlgorithmRunner::AlgorithmRunner(const CommandLineOptions &options) :
    graphFilename_(options.graphFilename),
    ssFilename_(options.ssFilename),
    p2pFilename_(options.p2pFilename),
    ossFilename_(options.ossFilename),
    op2pFilename_(options.op2pFilename),
    algorithmType_(options.algorithmType),
    experimentType_(chooseExperimentType())
{}

ExperimentType AlgorithmRunner::chooseExperimentType() const {
    return (!ssFilename_.empty()) ? ExperimentType::SOURCES : ExperimentType::PAIRS;
};

Graph AlgorithmRunner::createGraph(const std::string& graphFilename) {
    std::ifstream graphFile(graphFilename);
    if (!graphFile.is_open()) {
        std::cerr << "File at " << graphFilename << " can't be opened!\n";
        return Graph(1, true);
    }

    int numberOfVertices;
    std::string line;
    while (std::getline(graphFile, line)) {
        if (line[0] == 'p') {
            std::istringstream iss(line);
            std::string notNeeded;

            iss >> notNeeded >> notNeeded >> numberOfVertices >> notNeeded;
            break;
        }
    }

    Graph graph = Graph(numberOfVertices, true);

    while (std::getline(graphFile, line)) {
        if (line[0] == 'a') {
            std::istringstream iss(line);
            std::string notNeeded;
            int vertex1, vertex2, weight;

            iss >> notNeeded >> vertex1 >> vertex2 >> weight;

            graph.addEdge(--vertex1, --vertex2, weight);
        }
    }

    graphFile.close();

    return graph;
}

std::vector<int> AlgorithmRunner::parseSourcesFile() const {
    std::ifstream sourcesFile(ssFilename_);
    if (!sourcesFile.is_open()) {
        std::cerr << "File at " << ssFilename_ << " can't be opened!\n";
        return {};
    }

    std::vector<int> sources;

    std::string line;
    while (std::getline(sourcesFile, line)) {
        if (line[0] == 's') {
            std::istringstream iss(line);
            std::string notNeeded;
            int vertex;

            iss >> notNeeded >> vertex;

            sources.push_back(--vertex);
        }
    }

    sourcesFile.close();

    return sources;
}

std::vector<std::pair<int, int>> AlgorithmRunner::parsePairsFile() const {
    std::ifstream pairsFile(p2pFilename_);
    if (!pairsFile.is_open()) {
        std::cerr << "File at " << p2pFilename_ << " can't be opened!\n";
        return {};
    }

    std::vector<std::pair<int, int>> pairs;

    std::string line;
    while (std::getline(pairsFile, line)) {
        if (line[0] == 'q') {
            std::istringstream iss(line);
            std::string notNeeded;
            int vertex1, vertex2;

            iss >> notNeeded >> vertex1 >> vertex2;

            pairs.push_back({--vertex1, --vertex2});
        }
    }

    pairsFile.close();

    return pairs;
}

void AlgorithmRunner::runAlgorithm() const {
    std::ofstream outputFile((experimentType_ == ExperimentType::SOURCES) ? ossFilename_ : op2pFilename_);
    if (!outputFile.is_open()) {
        std::cerr << "File at " << p2pFilename_ << " can't be opened!\n";
        return;
    }

    const auto algorithmFunction = ALGORITHM_TYPE_TO_FUNCTION.at(algorithmType_);
    const Graph graph = createGraph(graphFilename_);

    if (experimentType_ == ExperimentType::SOURCES) {
        const std::vector<int> sources = parseSourcesFile();
        runSources(algorithmFunction, graph, sources, outputFile);
    } else {
        const std::vector<std::pair<int, int>> pairs = parsePairsFile();
        runPairs(algorithmFunction, graph, pairs, outputFile);
    }

    outputFile.close();
}

void AlgorithmRunner::runAlgorithmForSourcesWithoutParsing(std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction, const Graph& graph, const std::vector<int> &sources, const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "File at " << outputFilename << " can't be opened!\n";
        return;
    }

    runSources(algorithmFunction, graph, sources, outputFile);

    outputFile.close();
}

void AlgorithmRunner::runAlgorithmForPairsWithoutParsing(std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction, const Graph& graph, const std::vector<std::pair<int, int>> &pairs, const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "File at " << outputFilename << " can't be opened!\n";
        return;
    }

    runPairs(algorithmFunction, graph, pairs, outputFile);

    outputFile.close();
}

void AlgorithmRunner::runSources(
    std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction,
    const Graph& graph,
    std::vector<int> sources,
    std::ofstream& outputFile
) {
    std::chrono::nanoseconds totalDuration = std::chrono::nanoseconds(0);

    for (const auto& source : sources) {
        const auto startTime = std::chrono::high_resolution_clock::now();
        algorithmFunction(graph, source);
        const auto endTime = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalDuration += duration;
    }

    const auto averageDurationNanoseconds = totalDuration.count() / sources.size();
    const auto averageDurationMiliseconds = averageDurationNanoseconds / 1000000.0;
    outputFile << "t " << averageDurationMiliseconds << '\n';
}

void AlgorithmRunner::runPairs(
    std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction,
    const Graph& graph,
    std::vector<std::pair<int, int>> pairs,
    std::ofstream& outputFile
) {
    for (const auto& [sourceVertex, endVertex] : pairs) {
        const std::vector<long long> distances = algorithmFunction(graph, sourceVertex);

        outputFile << "d " << sourceVertex + 1 << " " << endVertex + 1 << " " << distances[endVertex] << '\n';
    }

}
