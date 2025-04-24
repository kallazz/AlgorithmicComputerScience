#include "State.hpp"

#include <algorithm>
#include <unordered_set>

State::State() : board({}), emptyRow(0), emptyColumn(0), costToReach(0), heuristicCost(0) {}

State::State(const std::vector<std::vector<int>>& initialBoard, const int initialEmptyTileRow,
             const int initialEmptyTileColumnumn, const int cost)
    : board(initialBoard),
      emptyRow(initialEmptyTileRow),
      emptyColumn(initialEmptyTileColumnumn),
      costToReach(cost),
      heuristicCost(0) {}

bool State::operator==(const State& other) const {
    return board == other.board;
}

size_t StateHash::operator()(const State& s) const {
    size_t hash = 0;
    for (const auto& row : s.board) {
        for (int val : row) {
            hash = hash * 31 + val;
        }
    }
    return hash;
}

bool CompareState::operator()(const State& a, const State& b) const {
    return (a.costToReach + a.heuristicCost) > (b.costToReach + b.heuristicCost);
}

bool isSolvable(const std::vector<std::vector<int>>& board, const int size) {
    std::vector<int> flattened;
    int blankRow = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 0) blankRow = i;
            flattened.push_back(board[i][j]);
        }
    }

    int inversionsCount = 0;
    for (size_t i = 0; i < flattened.size(); ++i)
        for (size_t j = i + 1; j < flattened.size(); ++j)
            if (flattened[i] && flattened[j] && flattened[i] > flattened[j]) ++inversionsCount;

    if (size % 2 == 1) {
        return inversionsCount % 2 == 0;
    } else {
        const int blankRowFromBottom = size - blankRow;
        return (inversionsCount + blankRowFromBottom) % 2 == 1;
    }
}

State generateRandomSolvableState(const int size, std::mt19937& gen) {
    std::vector<int> tiles(size * size - 1);
    for (int i = 0; i < size * size - 1; ++i) tiles[i] = i + 1;

    std::vector<std::vector<int>> board(size, std::vector<int>(size));
    const int emptyRow = size - 1;
    const int emptyColumn = size - 1;

    do {
        std::shuffle(tiles.begin(), tiles.end(), gen);

        for (int i = 0; i < size * size - 1; ++i) board[i / size][i % size] = tiles[i];

        board[emptyRow][emptyColumn] = 0;

    } while (!isSolvable(board, size));

    return State(board, emptyRow, emptyColumn);
}

State generateRandomSolvableStateByUndo(const int size, std::mt19937& gen, const int moveCount) {
    std::vector<std::vector<int>> board(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) board[i][j] = (i * size + j + 1) % (size * size);

    int emptyRow = size - 1, emptyColumn = size - 1;
    std::unordered_set<State, StateHash> visitedStates;
    visitedStates.insert(State(board, emptyRow, emptyColumn));

    std::vector<std::pair<int, int>> validMoves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < moveCount; ++i) {
        std::vector<std::tuple<int, int, std::vector<std::vector<int>>>> candidates;

        for (const auto& move : validMoves) {
            const int newRow = emptyRow + move.first;
            const int newColumn = emptyColumn + move.second;
            if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size) {
                auto newBoard = board;
                std::swap(newBoard[emptyRow][emptyColumn], newBoard[newRow][newColumn]);
                State candidateState(newBoard, newRow, newColumn);
                if (visitedStates.count(candidateState) == 0) {
                    candidates.emplace_back(newRow, newColumn, std::move(newBoard));
                }
            }
        }

        if (candidates.empty()) break;

        std::uniform_int_distribution<> dist(0, candidates.size() - 1);
        const auto [nextRow, nextColumn, nextBoard] = candidates[dist(gen)];

        board = std::move(nextBoard);
        emptyRow = nextRow;
        emptyColumn = nextColumn;
        visitedStates.insert(State(board, emptyRow, emptyColumn));
    }

    return State(board, emptyRow, emptyColumn);
}
