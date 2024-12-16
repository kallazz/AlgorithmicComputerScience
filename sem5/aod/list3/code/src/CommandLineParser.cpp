#include "CommandLineParser.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

void CommandLineParser::checkIfValueExists(const int i, const int argc, const std::string& optionName) {
    if (i + 1 >= argc) {
        throw std::invalid_argument("Option " + optionName +  " requires a value.");
    }
}

CommandLineOptions CommandLineParser::parseArgs(int argc, char* argv[]) {
    if (argc < 5) {
        throw std::invalid_argument("Insufficient arguments provided.");
    }

    CommandLineOptions options;
    bool p2pProvided = false;
    bool ssProvided = false;

    std::string algorithmName = argv[1];
    if (algorithmName != "dijkstra" && algorithmName != "dial" && algorithmName != "radixheap") {
        throw std::invalid_argument("Invalid algorithm name. Supported: dijkstra, dial, radixheap.");
    }
    options.algorithmType = getAlgorithmFromString(algorithmName);

    for (int i = 2; i < argc; ++i) {
        std::string argument = argv[i];

        if (argument == "-d") {
            checkIfValueExists(i, argc, "-d");
            options.graphFilename = argv[++i];
        } else if (argument == "-p2p") {
            checkIfValueExists(i, argc, "-p2p");
            options.p2pFilename = argv[++i];
            p2pProvided = true;
        } else if (argument == "-ss") {
            checkIfValueExists(i, argc, "-ss");
            options.ssFilename = argv[++i];
            ssProvided = true;
        } else if (argument == "-op2p") {
            checkIfValueExists(i, argc, "-op2p");
            if (!p2pProvided) {
                throw std::invalid_argument("Option -op2p can only be used if -p2p was provided.");
            }
            options.op2pFilename = argv[++i];
        } else if (argument == "-oss") {
            checkIfValueExists(i, argc, "-oss");
            if (!ssProvided) {
                throw std::invalid_argument("Option -oss can only be used if -ss was provided.");
            }
            options.ossFilename = argv[++i];
        } else {
            throw std::invalid_argument("Unknown argument: " + argument);
        }
    }

    if (options.graphFilename.empty()) {
        throw std::invalid_argument("Option -d is required.");
    }
    if (!p2pProvided && !ssProvided) {
        throw std::invalid_argument("Either option -p2p or -ss must be provided.");
    }
    if (p2pProvided && ssProvided) {
        throw std::invalid_argument("Option -p2p and -ss can't be both provided.");
    }

    return options;
}
