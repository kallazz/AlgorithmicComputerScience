#ifndef ALGORITHM_RUNNER_HPP
#define ALGORITHM_RUNNER_HPP

#include "CommandLineParser.hpp"
#include "Graph.hpp"

#include <functional>

class AlgorithmRunner {
public:
    AlgorithmRunner(const CommandLineOptions &options);

    void runAlgorithm() const;
    static void runAlgorithmForSourcesWithoutParsing(std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction,
        const Graph& graph, const std::vector<int> &sources, const std::string &outputFilename);
    static void runAlgorithmForPairsWithoutParsing(std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction,
        const Graph& graph, const std::vector<std::pair<int, int>> &pairs, const std::string &outputFilename);

    static Graph createGraph(const std::string& graphFilename);
private:
    ExperimentType chooseExperimentType() const;
    std::string chooseOutputFilename(const std::string &ossFilename, const std::string &op2pFilename) const;

    std::vector<int> parseSourcesFile() const;
    std::vector<std::pair<int, int>> parsePairsFile() const;

    static void runSources(
        const std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction,
        const Graph& graph,
        const std::vector<int> sources,
        std::ofstream& outputFile);
    static void runPairs(
        const std::function<std::vector<long long>(const Graph&, const int)> algorithmFunction,
        const Graph& graph,
        const std::vector<std::pair<int, int>> pairs,
        std::ofstream& outputFile);
    
    const std::string graphFilename_;
    const std::string ssFilename_;
    const std::string p2pFilename_;
    const std::string ossFilename_;
    const std::string op2pFilename_;
    const AlgorithmType algorithmType_;
    const ExperimentType experimentType_;
};

#endif // ALGORITHM_RUNNER_HPP
