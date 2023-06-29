#include "header.h"

int main() {
    vector<vector<uint8_t>> board(15, vector<uint8_t>(15, 0));
    int currentPlayer = -1;

    while (true) {
        printGomokuBoard(board);
        playerMove(board, currentPlayer);

        // Switch to the next player
        currentPlayer = -currentPlayer;
    }

    return 0;
}