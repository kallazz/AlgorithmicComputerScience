#include "aStar.hpp"

#include <queue>
#include <unordered_set>

int manhattanDistanceWithLinearConflict(const State& state, const int size) {
    int manhattanDistance = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value = state.board[i][j];
            if (value != 0) {
                int targetRow = (value - 1) / size;
                int targetColumn = (value - 1) % size;
                manhattanDistance += std::abs(i - targetRow) + std::abs(j - targetColumn);
            }
        }
    }

    int linearConflict = 0;

    // Row conflicts
    for (int row = 0; row < size; row++) {
        for (int column1 = 0; column1 < size - 1; column1++) {
            int val1 = state.board[row][column1];
            if (val1 == 0) continue;
            int targetRow1 = (val1 - 1) / size;
            if (targetRow1 != row) continue;

            for (int column2 = column1 + 1; column2 < size; column2++) {
                int val2 = state.board[row][column2];
                if (val2 == 0) continue;
                int targetRow2 = (val2 - 1) / size;
                if (targetRow2 != row) continue;

                int targetColumn1 = (val1 - 1) % size;
                int targetColumn2 = (val2 - 1) % size;

                if (targetColumn1 > targetColumn2) linearConflict++;
            }
        }
    }

    // Column conflicts
    for (int column = 0; column < size; column++) {
        for (int row1 = 0; row1 < size - 1; row1++) {
            int val1 = state.board[row1][column];
            if (val1 == 0) continue;
            int targetColumn1 = (val1 - 1) % size;
            if (targetColumn1 != column) continue;

            for (int row2 = row1 + 1; row2 < size; row2++) {
                int val2 = state.board[row2][column];
                if (val2 == 0) continue;
                int targetColumn2 = (val2 - 1) % size;
                if (targetColumn2 != column) continue;

                int targetRow1 = (val1 - 1) / size;
                int targetRow2 = (val2 - 1) / size;

                if (targetRow1 > targetRow2) linearConflict++;
            }
        }
    }

    return manhattanDistance + 2 * linearConflict;
}

int misplacedTiles(const State& state, const int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value = state.board[i][j];
            if (value != 0 && value != (i * size + j + 1)) {
                count++;
            }
        }
    }

    return count;
}

std::pair<std::vector<int>, int> solveAStar(State& initialState, const int size,
                                            const std::function<int(const State&, int)> heuristic) {
    std::priority_queue<State, std::vector<State>, CompareState> priorityQueue;
    std::unordered_set<State, StateHash> visitedStates;
    int visitedNodesCount = 0;

    initialState.heuristicCost = heuristic(initialState, size);
    priorityQueue.push(initialState);

    const int deltaRow[] = {-1, 1, 0, 0};
    const int deltaColumn[] = {0, 0, -1, 1};

    while (!priorityQueue.empty()) {
        State currentState = priorityQueue.top();
        priorityQueue.pop();
        visitedNodesCount++;

        if (visitedStates.count(currentState)) continue;
        visitedStates.insert(currentState);

        bool isSolved = true;
        for (int i = 0; i < size && isSolved; i++) {
            for (int j = 0; j < size && isSolved; j++) {
                if (currentState.board[i][j] != (i * size + j + 1) % (size * size)) {
                    isSolved = false;
                }
            }
        }
        if (isSolved) return {currentState.moves, visitedNodesCount};

        for (int i = 0; i < 4; i++) {
            const int newRow = currentState.emptyRow + deltaRow[i];
            const int newColumn = currentState.emptyColumn + deltaColumn[i];
            if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size) {
                State next(currentState.board, currentState.emptyRow, currentState.emptyColumn,
                           currentState.costToReach);
                next.moves = currentState.moves;

                std::swap(next.board[currentState.emptyRow][currentState.emptyColumn], next.board[newRow][newColumn]);
                next.emptyRow = newRow;
                next.emptyColumn = newColumn;
                next.costToReach++;
                next.heuristicCost = heuristic(next, size);
                next.moves.push_back(currentState.board[newRow][newColumn]);
                priorityQueue.push(next);
            }
        }
    }

    return {{}, visitedNodesCount};
}
