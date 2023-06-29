#include "header.h"

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