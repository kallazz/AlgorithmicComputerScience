#include "CommandLineParser.hpp"
#include "AlgorithmRunner.hpp"

int main(int argc, char* argv[]) {
    const CommandLineOptions options = CommandLineParser::parseArgs(argc, argv);
    const AlgorithmRunner runner = AlgorithmRunner(options);

    runner.runAlgorithm();

    return 0;
}
