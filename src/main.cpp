#include "header.h"

int main() {
    vector<vector<u_int8_t>> board(15, vector<u_int8_t>(15, 0));
    set<Pos> perimeter;
    int currentPlayer = 1;

    // printGomokuBoard(board);
    // playerMove(board, currentPlayer);
    // printGomokuBoard(board);
    // currentPlayer = currentPlayer^3;
    // Move best = getBestMove(board, currentPlayer, 3);
    // board[best.row][best.col] = currentPlayer;
    // cout << best.row << best.col << endl;
    // printGomokuBoard(board);
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
    // for (int i = 0; i < 3; i++)
    // {
    //     cout << currentPlayer << endl;
    //     currentPlayer = currentPlayer^3;
    // }
    
    return 0;
}