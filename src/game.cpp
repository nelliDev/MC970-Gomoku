#include "header.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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

    cout << "Player " << (player == -1 ? "X" : "O") << "'s turn. Enter the column (A-O) and row (0-14) to make a move: ";
    cin >> column >> row;

    int colIndex = column - 'A';

    if (row >= 0 && row < 15 && colIndex >= 0 && colIndex < 15 && board[row][colIndex] == 0) {
        board[row][colIndex] = player;
        addPerimiter(board, perim, row, colIndex);
    } else {
        cout << "Invalid move. Try again." << endl;
        playerMove(board, player, perim);
    }
}

void aiMove(vector<vector<u_int8_t>>& board, int player, int depth, set<Pos>& perim){

    Pos best = getBestMove(board, player, depth, perim);
    board[best.row][best.col] = player;
    addPerimiter(board, perim, best.row, best.col);
}

