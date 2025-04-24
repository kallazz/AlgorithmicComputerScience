#ifndef STATE_HPP
#define STATE_HPP

#include <random>
#include <vector>

struct State {
    std::vector<std::vector<int>> board;
    int emptyRow, emptyColumn;
    int costToReach;
    int heuristicCost;
    std::vector<int> moves;

    State();
    State(const std::vector<std::vector<int>>& initialBoard, const int initialEmptyTileRow,
          const int initialEmptyTileColumn, const int cost = 0);

    bool operator==(const State& other) const;
};

struct StateHash {
    size_t operator()(const State& s) const;
};

struct CompareState {
    bool operator()(const State& a, const State& b) const;
};

State generateRandomSolvableState(const int size, std::mt19937& gen);
State generateRandomSolvableStateByUndo(const int size, std::mt19937& gen, const int moveCount);

#endif  // STATE_HPP
