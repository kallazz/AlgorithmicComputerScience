#include "algorithms/kmp.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "Incorrect number of arguments. Please provide 2 arguments.\n";
        return 1;
    }

    const std::string pattern = argv[1];
    const std::string fileName = argv[2];

    if (!std::filesystem::exists(fileName)) {
        std::cout << "File does not exist.\n";
        return 1;
    }

    std::fstream file(fileName);
    std::string line;
    std::string text;

    while (std::getline(file, line)) {
        text += line;
        text += '\n';
    }

    const auto matches = kmpMatcher(text, pattern);

    std::cout << "Pattern: " << pattern << '\n';
    std::cout << "Text: " << text << '\n';

    if (matches.size() == 0) {
        std::cout << "No matches found.\n";
    } else {
        std::cout << "Matches:\n";

        for (const auto match : matches) {
            std::cout << "Pattern occurs with shift " << match << '\n';
        }
    }

    return 0;
}
