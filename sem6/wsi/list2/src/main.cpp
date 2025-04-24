#include "State.hpp"
#include "aStar.hpp"

#include <chrono>
#include <iostream>

void printBoard(const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row) {
            if (val == 0) {
                std::cout << "X"
                          << "\t";
            } else {
                std::cout << val << "\t";
            }
        }
        std::cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        std::cout << "Usage: " << argv[0]
                  << " <size: 3 or 4> <moves_count(0 for random shuffle)> [--ignore-misplaced]\n";
        return 1;
    }

    const int size = std::stoi(argv[1]);
    const int movesCount = std::stoi(argv[2]);
    const bool shouldIgnoreMisplaced = (argc == 4 && std::string(argv[3]) == "--ignore-misplaced");

    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    State initialState = (movesCount == 0) ? generateRandomSolvableState(size, gen)
                                           : generateRandomSolvableStateByUndo(size, gen, movesCount);

    std::cout << "Initial state:\n";
    printBoard(initialState.board);

    std::cout << "\nSolving with Manhattan Distance + Linear Conflict:\n";
    const auto start1 = std::chrono::steady_clock::now();
    const auto [moves1, nodes1] = solveAStar(initialState, size, manhattanDistanceWithLinearConflict);
    const auto end1 = std::chrono::steady_clock::now();
    const std::chrono::duration<double> duration1 = end1 - start1;

    std::cout << "Moves: ";
    for (int move : moves1) std::cout << move << " ";
    std::cout << "\nAmount of moves: " << moves1.size();
    std::cout << "\nNodes visited: " << nodes1;
    std::cout << "\nTime taken: " << duration1.count() << " seconds\n";

    if (!shouldIgnoreMisplaced) {
        std::cout << "\nSolving with Misplaced Tiles:\n";
        const auto start2 = std::chrono::steady_clock::now();
        const auto [moves2, nodes2] = solveAStar(initialState, size, misplacedTiles);
        const auto end2 = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration2 = end2 - start2;

        std::cout << "Moves: ";
        for (int move : moves2) std::cout << move << " ";
        std::cout << "\nAmount of moves: " << moves2.size();
        std::cout << "\nNodes visited: " << nodes2;
        std::cout << "\nTime taken: " << duration2.count() << " seconds\n";
    }

    return 0;
}
