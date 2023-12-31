#include "header.h"
#include "hashing.h"

int main() {
    vector<vector<u_int8_t>> board(15, vector<u_int8_t>(15, 0));
    set<Pos> perimeter;
    Pos nada;
    int currentPlayer = 2;
    initializeZobristTable();
    
    board [7][7] = 1;
    addPerimiter(board, perimeter, 7, 7, &nada);
    for (int i = 0; i < 7; i++){
        printGomokuBoard(board);
        aiMove(board, currentPlayer, 1, perimeter);
        currentPlayer ^= 3;
    }

    return 0;
}