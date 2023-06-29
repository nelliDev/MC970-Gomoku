#include <iostream>
#include <vector>

const int BOARD_SIZE = 15;

const int WIN_VALUE = 1000000;
const int TWO_VALUE = 1000;
const int THREE_VALUE = 100;
const int FOUR_VALUE = 10000;

// Function to check if a position is within the board bounds
bool isValidPosition(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

// Function to evaluate the current board state for a given player
int evaluatePosition(const std::vector<std::vector<int>>& board, int player) {
    int opponent = (player == 1) ? 2 : 1;
    int score = 0;

    // Evaluate rows
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col <= BOARD_SIZE - 5; col++) {
            int emptyCount = 0;
            int playerCount = 0;
            int opponentCount = 0;
            for (int i = 0; i < 5; i++) {
                int currRow = row;
                int currCol = col + i;
                int cell = board[currRow][currCol];
                if (cell == player)
                    playerCount++;
                else if (cell == opponent)
                    opponentCount++;
                else
                    emptyCount++;
            }
            if (emptyCount == 2 && playerCount == 3 && opponentCount == 0)
                score += THREE_VALUE;
            else if (emptyCount == 1 && playerCount == 4 && opponentCount == 0)
                score += FOUR_VALUE;
            else if (emptyCount == 0 && playerCount == 5 && opponentCount == 0)
                return WIN_VALUE;
        }
    }

    // Evaluate columns
    for (int col = 0; col < BOARD_SIZE; col++) {
        for (int row = 0; row <= BOARD_SIZE - 5; row++) {
            int emptyCount = 0;
            int playerCount = 0;
            int opponentCount = 0;
            for (int i = 0; i < 5; i++) {
                int currRow = row + i;
                int currCol = col;
                int cell = board[currRow][currCol];
                if (cell == player)
                    playerCount++;
                else if (cell == opponent)
                    opponentCount++;
                else
                    emptyCount++;
            }
            if (emptyCount == 2 && playerCount == 3 && opponentCount == 0)
                score += THREE_VALUE;
            else if (emptyCount == 1 && playerCount == 4 && opponentCount == 0)
                score += FOUR_VALUE;
            else if (emptyCount == 0 && playerCount == 5 && opponentCount == 0)
                return WIN_VALUE;
        }
    }

    // Evaluate diagonals (top-left to bottom-right)
    for (int row = 0; row <= BOARD_SIZE - 5; row++) {
        for (int col = 0; col <= BOARD_SIZE - 5; col++) {
            int emptyCount = 0;
            int playerCount = 0;
            int opponentCount = 0;
            for (int i = 0; i < 5; i++) {
                int currRow = row + i;
                int currCol = col + i;
                int cell = board[currRow][currCol];
                if (cell == player)
                    playerCount++;
                else if (cell == opponent)
                    opponentCount++;
                else
                    emptyCount++;
            }
            if (emptyCount == 2 && playerCount == 3 && opponentCount == 0)
                score += THREE_VALUE;
            else if (emptyCount == 1 && playerCount == 4 && opponentCount == 0)
                score += FOUR_VALUE;
            else if (emptyCount == 0 && playerCount == 5 && opponentCount == 0)
                return WIN_VALUE;
        }
    }

    // Evaluate diagonals (top-right to bottom-left)
    for (int row = 0; row <= BOARD_SIZE - 5; row++) {
        for (int col = BOARD_SIZE - 1; col >= 4; col--) {
            int emptyCount = 0;
            int playerCount = 0;
            int opponentCount = 0;
            for (int i = 0; i < 5; i++) {
                int currRow = row + i;
                int currCol = col - i;
                int cell = board[currRow][currCol];
                if (cell == player)
                    playerCount++;
                else if (cell == opponent)
                    opponentCount++;
                else
                    emptyCount++;
            }
            if (emptyCount == 2 && playerCount == 3 && opponentCount == 0)
                score += THREE_VALUE;
            else if (emptyCount == 1 && playerCount == 4 && opponentCount == 0)
                score += FOUR_VALUE;
            else if (emptyCount == 0 && playerCount == 5 && opponentCount == 0)
                return WIN_VALUE;
        }
    }

    return score;
}

// Function to choose the best move given the current board state and player's turn
std::pair<int, int> chooseBestMove(const std::vector<std::vector<int>>& board, int player) {
    int bestScore = INT_MIN;
    std::pair<int, int> bestMove = {-1, -1};

    // Iterate through all positions on the board
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Check if the position is empty
            if (board[row][col] == 0) {
                // Make a copy of the board
                std::vector<std::vector<int>> newBoard = board;
                // Place the player's move on the copied board
                newBoard[row][col] = player;
                // Evaluate the position for the player
                int score = evaluatePosition(newBoard, player);
                // Update the best move if a better score is found
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {row, col};
                }
            }
        }
    }

    return bestMove;
}

// Function to print the board
void printBoard(const std::vector<std::vector<int>>& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Example usage
    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Choose the best move for player 1 (X)
    std::pair<int, int> bestMove = chooseBestMove(board, 1);

    std::cout << "Best Move: " << bestMove.first << ", " << bestMove.second << std::endl;

    return 0;
}
