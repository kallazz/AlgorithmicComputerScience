#include "codes.hpp"
#include "compression.hpp"
#include <iostream>

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    if (argc < 5) {
        std::cerr << "Usage: program encode|decode input output code(omega|gamma|delta|fib)\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];
    std::string codeType = argv[4];

    initializeFibonacciSequence();

    try {
        if (mode == "encode") {
            encodeFile(inputFile, outputFile, codeType);
        } else if (mode == "decode") {
            decodeFile(inputFile, outputFile, codeType);
        } else {
            std::cerr << "Mode must be 'encode' or 'decode'\n";
            return 1;
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
