#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

// Constant definitions for game management
constexpr int BOARD_SIZE = 5;
constexpr int EMPTY = 0;
constexpr int PLAYER_X = 1;
constexpr int PLAYER_O = 2;
constexpr int WIN_LENGTH = 4;
constexpr int LOSE_LENGTH = 3;
constexpr int MAX_DEPTH = 10;

// Server communication codes
constexpr int MSG_YOUR_TURN = 0;
constexpr int MSG_YOU_WIN = 1;
constexpr int MSG_YOU_LOSE = 2;
constexpr int MSG_DRAW = 3;
constexpr int MSG_OPPONENT_ERROR = 4;
constexpr int MSG_YOUR_ERROR = 5;
constexpr int MSG_CONTINUE_TURN = 6;

// Evaluation values for the minimax algorithm
constexpr int SCORE_WIN = 1000;
constexpr int SCORE_LOSE = -1000;
constexpr int SCORE_DRAW = 0;
constexpr int SCORE_CENTER_POSITION = 2;
constexpr int SCORE_GAPPED_SEQUENCE = 500;  // Value for sequences with a gap (e.g., XX_X)

int gameBoard[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            gameBoard[rowIndex][colIndex] = EMPTY;
        }
    }
}

bool isValidMove(int movePosition) {
    int rowIndex = movePosition / 10 - 1;
    int colIndex = movePosition % 10 - 1;

    if (rowIndex < 0 || rowIndex >= BOARD_SIZE || colIndex < 0 || colIndex >= BOARD_SIZE) {
        return false;
    }

    return gameBoard[rowIndex][colIndex] == EMPTY;
}

bool makeMove(int movePosition, int currentPlayer) {
    if (!isValidMove(movePosition)) {
        return false;
    }

    int rowIndex = movePosition / 10 - 1;
    int colIndex = movePosition % 10 - 1;
    gameBoard[rowIndex][colIndex] = currentPlayer;

    return true;
}

void undoMove(int movePosition) {
    int rowIndex = movePosition / 10 - 1;
    int colIndex = movePosition % 10 - 1;
    gameBoard[rowIndex][colIndex] = EMPTY;
}

bool hasPlayerWon(int playerSymbol) {
    // Check horizontally
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex <= BOARD_SIZE - WIN_LENGTH; colIndex++) {
            bool isWinningSequence = true;
            for (int offset = 0; offset < WIN_LENGTH; offset++) {
                if (gameBoard[rowIndex][colIndex + offset] != playerSymbol) {
                    isWinningSequence = false;
                    break;
                }
            }
            if (isWinningSequence) return true;
        }
    }

    // Check vertically
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - WIN_LENGTH; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            bool isWinningSequence = true;
            for (int offset = 0; offset < WIN_LENGTH; offset++) {
                if (gameBoard[rowIndex + offset][colIndex] != playerSymbol) {
                    isWinningSequence = false;
                    break;
                }
            }
            if (isWinningSequence) return true;
        }
    }

    // Check diagonal (\)
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - WIN_LENGTH; rowIndex++) {
        for (int colIndex = 0; colIndex <= BOARD_SIZE - WIN_LENGTH; colIndex++) {
            bool isWinningSequence = true;
            for (int offset = 0; offset < WIN_LENGTH; offset++) {
                if (gameBoard[rowIndex + offset][colIndex + offset] != playerSymbol) {
                    isWinningSequence = false;
                    break;
                }
            }
            if (isWinningSequence) return true;
        }
    }

    // Check diagonal (/)
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - WIN_LENGTH; rowIndex++) {
        for (int colIndex = WIN_LENGTH - 1; colIndex < BOARD_SIZE; colIndex++) {
            bool isWinningSequence = true;
            for (int offset = 0; offset < WIN_LENGTH; offset++) {
                if (gameBoard[rowIndex + offset][colIndex - offset] != playerSymbol) {
                    isWinningSequence = false;
                    break;
                }
            }
            if (isWinningSequence) return true;
        }
    }

    return false;
}

bool hasPlayerLost(int playerSymbol) {
    // Check horizontally
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex <= BOARD_SIZE - LOSE_LENGTH; colIndex++) {
            bool isLosingSequence = true;
            for (int offset = 0; offset < LOSE_LENGTH; offset++) {
                if (gameBoard[rowIndex][colIndex + offset] != playerSymbol) {
                    isLosingSequence = false;
                    break;
                }
            }
            // Check if it's not part of a four-in-a-row
            if (isLosingSequence) {
                // Check left side
                if (colIndex > 0 && gameBoard[rowIndex][colIndex - 1] == playerSymbol) {
                    isLosingSequence = false;
                }
                // Check right side
                if (colIndex + LOSE_LENGTH < BOARD_SIZE && gameBoard[rowIndex][colIndex + LOSE_LENGTH] == playerSymbol) {
                    isLosingSequence = false;
                }
                if (isLosingSequence) return true;
            }
        }
    }

    // Check vertically
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - LOSE_LENGTH; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            bool isLosingSequence = true;
            for (int offset = 0; offset < LOSE_LENGTH; offset++) {
                if (gameBoard[rowIndex + offset][colIndex] != playerSymbol) {
                    isLosingSequence = false;
                    break;
                }
            }
            // Check if it's not part of a four-in-a-row
            if (isLosingSequence) {
                // Check top side
                if (rowIndex > 0 && gameBoard[rowIndex - 1][colIndex] == playerSymbol) {
                    isLosingSequence = false;
                }
                // Check bottom side
                if (rowIndex + LOSE_LENGTH < BOARD_SIZE && gameBoard[rowIndex + LOSE_LENGTH][colIndex] == playerSymbol) {
                    isLosingSequence = false;
                }
                if (isLosingSequence) return true;
            }
        }
    }

    // Check diagonal (\)
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - LOSE_LENGTH; rowIndex++) {
        for (int colIndex = 0; colIndex <= BOARD_SIZE - LOSE_LENGTH; colIndex++) {
            bool isLosingSequence = true;
            for (int offset = 0; offset < LOSE_LENGTH; offset++) {
                if (gameBoard[rowIndex + offset][colIndex + offset] != playerSymbol) {
                    isLosingSequence = false;
                    break;
                }
            }
            // Check if it's not part of a four-in-a-row
            if (isLosingSequence) {
                // Check top-left side
                if (rowIndex > 0 && colIndex > 0 && gameBoard[rowIndex - 1][colIndex - 1] == playerSymbol) {
                    isLosingSequence = false;
                }
                // Check bottom-right side
                if (rowIndex + LOSE_LENGTH < BOARD_SIZE && colIndex + LOSE_LENGTH < BOARD_SIZE &&
                    gameBoard[rowIndex + LOSE_LENGTH][colIndex + LOSE_LENGTH] == playerSymbol) {
                    isLosingSequence = false;
                }
                if (isLosingSequence) return true;
            }
        }
    }

    // Check diagonal (/)
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - LOSE_LENGTH; rowIndex++) {
        for (int colIndex = LOSE_LENGTH - 1; colIndex < BOARD_SIZE; colIndex++) {
            bool isLosingSequence = true;
            for (int offset = 0; offset < LOSE_LENGTH; offset++) {
                if (gameBoard[rowIndex + offset][colIndex - offset] != playerSymbol) {
                    isLosingSequence = false;
                    break;
                }
            }
            // Check if it's not part of a four-in-a-row
            if (isLosingSequence) {
                // Check top-right side
                if (rowIndex > 0 && colIndex + 1 < BOARD_SIZE && gameBoard[rowIndex - 1][colIndex + 1] == playerSymbol) {
                    isLosingSequence = false;
                }
                // Check bottom-left side
                if (rowIndex + LOSE_LENGTH < BOARD_SIZE && colIndex - LOSE_LENGTH >= 0 &&
                    gameBoard[rowIndex + LOSE_LENGTH][colIndex - LOSE_LENGTH] == playerSymbol) {
                    isLosingSequence = false;
                }
                if (isLosingSequence) return true;
            }
        }
    }

    return false;
}

bool isBoardFull() {
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            if (gameBoard[rowIndex][colIndex] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

std::vector<int> generatePossibleMoves() {
    static std::mt19937 generator(std::random_device{}());

    std::vector<int> availableMoves;
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            if (gameBoard[rowIndex][colIndex] == EMPTY) {
                availableMoves.push_back((rowIndex + 1) * 10 + (colIndex + 1));
            }
        }
    }

    // Shuffle moves for greater game variety
    std::shuffle(availableMoves.begin(), availableMoves.end(), generator);

    return availableMoves;
}

int evaluateSequenceValue(int sequenceLength, int openEndsCount) {
    if (sequenceLength >= WIN_LENGTH) return SCORE_WIN;

    switch (sequenceLength) {
        case 1:
            return openEndsCount * 1;  // Single symbol has low value
        case 2:
            return openEndsCount * 5;  // Two symbols are much better
        case 3:
            return SCORE_LOSE;
        default:
            return 0;
    }
}

int evaluateContinuousSequences(int playerSymbol) {
    int sequenceScore = 0;

    // Evaluate continuous horizontal sequences
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            if (gameBoard[rowIndex][colIndex] == playerSymbol) {
                int sequenceLength = 1;
                int openEndsCount = 0;

                if (colIndex > 0 && gameBoard[rowIndex][colIndex - 1] == EMPTY) openEndsCount++;

                for (int offset = 1; colIndex + offset < BOARD_SIZE && gameBoard[rowIndex][colIndex + offset] == playerSymbol; offset++) {
                    sequenceLength++;
                }

                if (colIndex + sequenceLength < BOARD_SIZE && gameBoard[rowIndex][colIndex + sequenceLength] == EMPTY) openEndsCount++;

                sequenceScore += evaluateSequenceValue(sequenceLength, openEndsCount);
            }
        }
    }

    // Evaluate continuous vertical sequences
    for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
        for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
            if (gameBoard[rowIndex][colIndex] == playerSymbol) {
                int sequenceLength = 1;
                int openEndsCount = 0;

                if (rowIndex > 0 && gameBoard[rowIndex - 1][colIndex] == EMPTY) openEndsCount++;

                for (int offset = 1; rowIndex + offset < BOARD_SIZE && gameBoard[rowIndex + offset][colIndex] == playerSymbol; offset++) {
                    sequenceLength++;
                }

                if (rowIndex + sequenceLength < BOARD_SIZE && gameBoard[rowIndex + sequenceLength][colIndex] == EMPTY) openEndsCount++;

                sequenceScore += evaluateSequenceValue(sequenceLength, openEndsCount);
            }
        }
    }

    // Evaluate continuous diagonal sequences (\)
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            if (gameBoard[rowIndex][colIndex] == playerSymbol) {
                int sequenceLength = 1;
                int openEndsCount = 0;

                if (rowIndex > 0 && colIndex > 0 && gameBoard[rowIndex - 1][colIndex - 1] == EMPTY) openEndsCount++;

                for (int offset = 1; rowIndex + offset < BOARD_SIZE && colIndex + offset < BOARD_SIZE &&
                                     gameBoard[rowIndex + offset][colIndex + offset] == playerSymbol;
                     offset++) {
                    sequenceLength++;
                }

                if (rowIndex + sequenceLength < BOARD_SIZE && colIndex + sequenceLength < BOARD_SIZE &&
                    gameBoard[rowIndex + sequenceLength][colIndex + sequenceLength] == EMPTY)
                    openEndsCount++;

                sequenceScore += evaluateSequenceValue(sequenceLength, openEndsCount);
            }
        }
    }

    // Evaluate continuous diagonal sequences (/)
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
            if (gameBoard[rowIndex][colIndex] == playerSymbol) {
                int sequenceLength = 1;
                int openEndsCount = 0;

                if (rowIndex > 0 && colIndex + 1 < BOARD_SIZE && gameBoard[rowIndex - 1][colIndex + 1] == EMPTY) openEndsCount++;

                for (int offset = 1; rowIndex + offset < BOARD_SIZE && colIndex - offset >= 0 &&
                                     gameBoard[rowIndex + offset][colIndex - offset] == playerSymbol;
                     offset++) {
                    sequenceLength++;
                }

                if (rowIndex + sequenceLength < BOARD_SIZE && colIndex - sequenceLength >= 0 &&
                    gameBoard[rowIndex + sequenceLength][colIndex - sequenceLength] == EMPTY)
                    openEndsCount++;

                sequenceScore += evaluateSequenceValue(sequenceLength, openEndsCount);
            }
        }
    }

    return sequenceScore;
}

int evaluateGappedSequences(int playerSymbol) {
    int gappedScore = 0;

    // Check horizontally
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex <= BOARD_SIZE - 4; colIndex++) {
            // Patterns: XX_X or X_XX
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex][colIndex + 1] == playerSymbol &&
                gameBoard[rowIndex][colIndex + 2] == EMPTY && gameBoard[rowIndex][colIndex + 3] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex][colIndex + 1] == EMPTY &&
                gameBoard[rowIndex][colIndex + 2] == playerSymbol && gameBoard[rowIndex][colIndex + 3] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
        }
    }

    // Check vertically
    for (int colIndex = 0; colIndex < BOARD_SIZE; colIndex++) {
        for (int rowIndex = 0; rowIndex <= BOARD_SIZE - 4; rowIndex++) {
            // Patterns: XX_X or X_XX
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex + 1][colIndex] == playerSymbol &&
                gameBoard[rowIndex + 2][colIndex] == EMPTY && gameBoard[rowIndex + 3][colIndex] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex + 1][colIndex] == EMPTY &&
                gameBoard[rowIndex + 2][colIndex] == playerSymbol && gameBoard[rowIndex + 3][colIndex] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
        }
    }

    // Check diagonal (\)
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - 4; rowIndex++) {
        for (int colIndex = 0; colIndex <= BOARD_SIZE - 4; colIndex++) {
            // Patterns: XX_X or X_XX
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex + 1][colIndex + 1] == playerSymbol &&
                gameBoard[rowIndex + 2][colIndex + 2] == EMPTY && gameBoard[rowIndex + 3][colIndex + 3] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex + 1][colIndex + 1] == EMPTY &&
                gameBoard[rowIndex + 2][colIndex + 2] == playerSymbol && gameBoard[rowIndex + 3][colIndex + 3] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
        }
    }

    // Check diagonal (/)
    for (int rowIndex = 0; rowIndex <= BOARD_SIZE - 4; rowIndex++) {
        for (int colIndex = 3; colIndex < BOARD_SIZE; colIndex++) {
            // Patterns: XX_X or X_XX
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex + 1][colIndex - 1] == playerSymbol &&
                gameBoard[rowIndex + 2][colIndex - 2] == EMPTY && gameBoard[rowIndex + 3][colIndex - 3] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
            if (gameBoard[rowIndex][colIndex] == playerSymbol && gameBoard[rowIndex + 1][colIndex - 1] == EMPTY &&
                gameBoard[rowIndex + 2][colIndex - 2] == playerSymbol && gameBoard[rowIndex + 3][colIndex - 3] == playerSymbol) {
                gappedScore += SCORE_GAPPED_SEQUENCE;
            }
        }
    }

    return gappedScore;
}

int evaluateSequences(int playerSymbol, int opponentSymbol) {
    return evaluateContinuousSequences(playerSymbol) + evaluateGappedSequences(playerSymbol);
}

/*
 * Heuristic evaluation function for the board.
 *
 * The heuristic considers the following factors:
 * 1. **Game termination conditions**:
 *    - AI player win (four symbols in a row): +1000 points.
 *    - AI player loss (three symbols in a row or four opponent symbols): -1000 points.
 *    - Opponent win (four symbols in a row): -1000 points.
 *    - Opponent loss (three symbols in a row): +1000 points.
 *    These values have the highest priority and are returned immediately if any of these conditions are met.
 *
 * 2. **Sequence evaluation**:
 *    Sequences are evaluated separately for the AI player and the opponent. The opponent's score is subtracted from the AI player's score.
 *    - **Continuous sequences** (evaluateContinuousSequences):
 *      - Sequence of length 1:
 *        - With one open end (empty space on one side): +1 point.
 *        - With two open ends (empty spaces on both sides): +2 points.
 *      - Sequence of length 2:
 *        - With one open end: +5 points.
 *        - With two open ends: +10 points.
 *      - Sequence of length 3 (not part of a four): -1000 points (causes a loss).
 *      - Sequence of length 4 or more: +1000 points (causes a win).
 *    - **Gapped sequences** (evaluateGappedSequences):
 *      - Patterns like XX_X or X_XX (three symbols with one empty space between them): +500 points.
 *        These sequences are highly valued because one move (occupying the empty space) creates a line of four symbols, leading to a win.
 *    Sequences are checked in all directions: horizontally, vertically, diagonally (\), and diagonally (/).
 *
 * 3. **Central positions**:
 *    - AI player symbol in central board positions (rows and columns 1, 2, 3, excluding edges): +2 points per position.
 *    - Opponent symbol in central positions: -2 points per position.
 *    Central positions are rewarded because they increase opportunities to create lines in multiple directions.
 *
 * **Score calculation mechanism**:
 * - The total score is the sum of points for the AI player's sequences minus the sum of points for the opponent's sequences, plus/minus
 * points for central positions.
 * - A positive score indicates a position favorable to the AI player, a negative score favors the opponent, and zero indicates a neutral
 * position.
 *
 * Returns a positive value if the position is favorable for the AI player, negative if favorable for the opponent, and 0 if neutral.
 */
int evaluateBoard(int playerSymbol) {
    int opponentSymbol = (playerSymbol == PLAYER_X) ? PLAYER_O : PLAYER_X;
    int totalScore = 0;

    // Evaluation for the player
    totalScore += evaluateSequences(playerSymbol, opponentSymbol);

    // Evaluation for the opponent (negated)
    totalScore -= evaluateSequences(opponentSymbol, playerSymbol);

    // Promote central positions
    for (int rowIndex = 1; rowIndex < BOARD_SIZE - 1; rowIndex++) {
        for (int colIndex = 1; colIndex < BOARD_SIZE - 1; colIndex++) {
            if (gameBoard[rowIndex][colIndex] == playerSymbol) {
                totalScore += SCORE_CENTER_POSITION;
            } else if (gameBoard[rowIndex][colIndex] == opponentSymbol) {
                totalScore -= SCORE_CENTER_POSITION;
            }
        }
    }

    return totalScore;
}

int minimax(const int depth, const bool isMaximizing, int alpha, int beta, const int aiPlayerSymbol) {
    const int opponentSymbol = (aiPlayerSymbol == PLAYER_X) ? PLAYER_O : PLAYER_X;

    if (hasPlayerWon(aiPlayerSymbol)) return SCORE_WIN + depth;
    if (hasPlayerWon(opponentSymbol)) return SCORE_LOSE - depth;
    if (hasPlayerLost(aiPlayerSymbol)) return SCORE_LOSE - depth;
    if (hasPlayerLost(opponentSymbol)) return SCORE_WIN + depth;
    if (isBoardFull()) return SCORE_DRAW;
    if (depth == 0) return evaluateBoard(aiPlayerSymbol);

    std::vector<int> possibleMoves = generatePossibleMoves();

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int movePosition : possibleMoves) {
            if (makeMove(movePosition, aiPlayerSymbol)) {
                const int score = minimax(depth - 1, false, alpha, beta, aiPlayerSymbol);
                undoMove(movePosition);
                bestScore = std::max(bestScore, score);
                alpha = std::max(alpha, bestScore);
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int movePosition : possibleMoves) {
            if (makeMove(movePosition, opponentSymbol)) {
                const int score = minimax(depth - 1, true, alpha, beta, aiPlayerSymbol);
                undoMove(movePosition);
                bestScore = std::min(bestScore, score);
                beta = std::min(beta, bestScore);
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    }
}

int findBestMove(int playerSymbol, int searchDepth) {
    int bestScore = INT_MIN;
    int bestMove = -1;

    std::vector<int> possibleMoves = generatePossibleMoves();

    for (int movePosition : possibleMoves) {
        if (makeMove(movePosition, playerSymbol)) {
            // Check for immediate win
            if (hasPlayerWon(playerSymbol)) {
                undoMove(movePosition);
                return movePosition;
            }

            // Check if the move causes a loss by forming three in a row
            if (hasPlayerLost(playerSymbol)) {
                undoMove(movePosition);
                continue;  // Skip losing moves
            }

            int score = minimax(searchDepth - 1, false, INT_MIN, INT_MAX, playerSymbol);
            undoMove(movePosition);

            if (score > bestScore) {
                bestScore = score;
                bestMove = movePosition;
            }
        }
    }

    // If no good move is found, choose the first valid move
    if (bestMove == -1 && !possibleMoves.empty()) {
        bestMove = possibleMoves[0];
    }

    return bestMove;
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Usage: %s <ip_address> <port> <player_number> <player_name> <depth>\n", argv[0]);
        return -1;
    }
    // Initialize data
    char* serverIp = argv[1];
    int port = atoi(argv[2]);
    int player = atoi(argv[3]);
    char* playerName = argv[4];
    int depth = atoi(argv[5]);
    // Validate input data
    if (player != PLAYER_X && player != PLAYER_O) {
        printf("Invalid player number (should be 1 or 2)\n");
        return -1;
    }
    if (depth < 1 || depth > MAX_DEPTH) {
        printf("Invalid depth (should be from 1 to %d)\n", MAX_DEPTH);
        return -1;
    }
    // Initialize socket
    int serverSocket;
    struct sockaddr_in serverAddr;
    char serverMessage[16], playerMessage[16];
    bool endGame;
    int msg, move;
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    // Set port and IP address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);
    // Send connection request to the server
    if (connect(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Unable to connect to the server\n");
        return -1;
    }
    printf("Connected to the server\n");
    // Receive message from the server
    memset(serverMessage, '\0', sizeof(serverMessage));
    if (recv(serverSocket, serverMessage, sizeof(serverMessage), 0) < 0) {
        printf("Error receiving message from the server\n");
        return -1;
    }
    // Send player data to the server
    memset(playerMessage, '\0', sizeof(playerMessage));
    snprintf(playerMessage, sizeof(playerMessage), "%d %s", player, playerName);
    if (send(serverSocket, playerMessage, strlen(playerMessage), 0) < 0) {
        printf("Unable to send message\n");
        return -1;
    }
    // Initialize the board
    initializeBoard();
    endGame = false;
    // Main game loop
    while (!endGame) {
        memset(serverMessage, '\0', sizeof(serverMessage));
        if (recv(serverSocket, serverMessage, sizeof(serverMessage), 0) < 0) {
            printf("Error receiving message from the server\n");
            return -1;
        }
        sscanf(serverMessage, "%d", &msg);
        move = msg % 100;
        msg = msg / 100;
        // Handle opponent's move
        if (move != 0) {
            makeMove(move, (player == PLAYER_X) ? PLAYER_O : PLAYER_X);
        }
        // Handle messages
        if (msg == 0 || msg == 6) {
            // Our turn to move - use minimax
            move = findBestMove(player, depth);
            // Execute the move
            makeMove(move, player);
            // Send the move to the server
            memset(playerMessage, '\0', sizeof(playerMessage));
            snprintf(playerMessage, sizeof(playerMessage), "%d", move);
            if (send(serverSocket, playerMessage, strlen(playerMessage), 0) < 0) {
                printf("Unable to send message\n");
                return -1;
            }
        } else {
            // End of the game
            endGame = true;
            switch (msg) {
                case 1:
                    printf("You won.\n");
                    break;
                case 2:
                    printf("You lost.\n");
                    break;
                case 3:
                    printf("Draw.\n");
                    break;
                case 4:
                    printf("You won. Opponent error.\n");
                    break;
                case 5:
                    printf("You lost. Your error.\n");
                    break;
            }
        }
    }
    // Close the socket
    close(serverSocket);
    return 0;
}
