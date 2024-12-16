#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include "enums.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

struct CommandLineOptions {
    AlgorithmType algorithmType;
    std::string graphFilename;
    std::string p2pFilename;
    std::string ssFilename;
    std::string op2pFilename;
    std::string ossFilename;
};

class CommandLineParser {
public:
    static CommandLineOptions parseArgs(int argc, char* argv[]);

private:
    static void checkIfValueExists(const int i, const int argc, const std::string& optionName);
};

#endif // COMMAND_LINE_PARSER_HPP