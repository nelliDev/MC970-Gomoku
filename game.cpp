#include <iostream>
#include <iomanip>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

bool checkWin(const vector<vector<int>>& board, int player, int row, int col) {
    // Check horizontal
    int count = 0;
    for (int i = col - 4; i <= col + 4; i++) {
        if (i >= 0 && i < 15 && board[row][i] == player) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    // Check vertical
    count = 0;
    for (int i = row - 4; i <= row + 4; i++) {
        if (i >= 0 && i < 15 && board[i][col] == player) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    // Check diagonal (top-left to bottom-right)
    count = 0;
    for (int i = -4; i <= 4; i++) {
        int r = row + i;
        int c = col + i;
        if (r >= 0 && r < 15 && c >= 0 && c < 15 && board[r][c] == player) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    // Check diagonal (top-right to bottom-left)
    count = 0;
    for (int i = -4; i <= 4; i++) {
        int r = row - i;
        int c = col + i;
        if (r >= 0 && r < 15 && c >= 0 && c < 15 && board[r][c] == player) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    return false;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printGomokuBoard(const vector<vector<int>>& board) {
    clearScreen();

    // ANSI escape sequences for text colors
    const string colorDark = "\x1B[1;31m";  // Red
    const string colorLight = "\x1B[1;34m"; // Blue
    const string colorReset = "\x1B[0m";    // Reset to default

    // Print the column letters
    cout << "   ";
    for (char c = 'A'; c <= 'O'; c++) {
        cout << c << " ";
    }
    cout << endl;

    // Print the rows
    for (int i = 0; i < 15; i++) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < 15; j++) {
            if (board[i][j] == -1) {
                cout << colorDark << "X " << colorReset;
            } else if (board[i][j] == 1) {
                cout << colorLight << "O " << colorReset;
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

void playerMove(vector<vector<int>>& board, int player) {
    char column;
    int row;

    cout << "Player " << (player == -1 ? "X" : "O") << "'s turn. Enter the column (A-O) and row (0-14) to make a move: ";
    cin >> column >> row;

    int colIndex = column - 'A';

    if (row >= 0 && row < 15 && colIndex >= 0 && colIndex < 15 && board[row][colIndex] == 0) {
        board[row][colIndex] = player;
        if (checkWin(board, player, row, colIndex)) {
            printGomokuBoard(board);
            cout << "Player " << (player == -1 ? "X" : "O") << " wins! Congratulations!" << endl;
            exit(0);
        }
    } else {
        cout << "Invalid move. Try again." << endl;
        playerMove(board, player);
    }
}

void aiMove(vector<vector<int>>& board, int player) {
    // Create an instance of your AI player class
    YourAIPlayer aiPlayer;

    // Generate the child states for the current game state
    vector<GameState> childStates = aiPlayer.generateChildStates(board, player);

    // Select the best move based on the AI player's strategy
    GameState bestMove = aiPlayer.selectBestMove(childStates);

    // Apply the AI player's move to the board
    board = bestMove.gameBoard;

    if (checkWin(board, player, bestMove.row, bestMove.col)) {
        printGomokuBoard(board);
        cout << "Player " << (player == -1 ? "X" : "O") << " wins! Congratulations!" << endl;
        exit(0);
    }
}

int main() {
    vector<vector<int>> board(15, vector<int>(15, 0));
    int currentPlayer = -1;

    while (true) {
        printGomokuBoard(board);
        playerMove(board, currentPlayer);

        // Switch to the next player
        currentPlayer = -currentPlayer;
    }

    return 0;
}
