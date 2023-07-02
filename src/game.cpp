#include "header.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool checkWin(const vector<vector<u_int8_t>>& board, int player, int row, int col) {
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

void printGomokuBoard(const vector<vector<u_int8_t>>& board) {
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
            if (board[i][j] == 1) {
                cout << colorDark << "X " << colorReset;
            } else if (board[i][j] == 2) {
                cout << colorLight << "O " << colorReset;
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}



void playerMove(vector<vector<u_int8_t>>& board, int player, set<Pos>& perim) {
    char column;
    int row;
    Pos nada;

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
        addPerimiter(board, perim, row, colIndex, &nada);
    } else {
        cout << "Invalid move. Try again." << endl;
        playerMove(board, player, perim);
    }
}

void aiMove(vector<vector<u_int8_t>>& board, int player, int depth, set<Pos>& perim){
    Pos nada;
    Pos best = getBestMove(board, player, depth, perim);
    board[best.row][best.col] = player;
    if (checkWin(board, player, best.row, best.col)) {
        printGomokuBoard(board);
        cout << "Player " << (player == -1 ? "X" : "O") << " wins! Congratulations!" << endl;
        exit(0);
    }
    addPerimiter(board, perim, best.row, best.col, &nada);
}

