#include "header.h"
#include "hashing.h"

int main() {
    vector<vector<u_int8_t>> board(15, vector<u_int8_t>(15, 0));
    set<Pos> perimeter;
    int currentPlayer = 1;
    initializeZobristTable();

    while (true) {
        printGomokuBoard(board);
        if (currentPlayer == 1)
        {
            playerMove(board, currentPlayer, perimeter);
        }
        else
        {
            aiMove(board, currentPlayer, 1, perimeter);
        }
        
        
        // Switch to the next player
        currentPlayer = currentPlayer^3;
    }
    
    return 0;
}