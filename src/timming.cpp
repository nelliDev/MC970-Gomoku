#include "header.h"

// int main() {
//     vector<vector<u_int8_t>> board(15, vector<u_int8_t>(15, 0));
//     set<Pos> perimeter;
//     Pos nada;
//     int currentPlayer = 1;
//     int moves[][2] = {{4, 4}, {10, 4}, {4, 10}, {10, 10}};

//     for (int i = 0; i < 4; i++){
//         printGomokuBoard(board);
//         board[moves[i][0]][moves[i][1]] = 1;
//         addPerimiter(board, perimeter, moves[i][0], moves[i][1], &nada);
//         printGomokuBoard(board);
//         aiMove(board, 2, 1, perimeter);
//     }

//     return 0;
// }

int main() {
    vector<vector<u_int8_t>> board(15, vector<u_int8_t>(15, 0));
    set<Pos> perimeter;
    Pos nada;
    int currentPlayer = 2;

    board[7][7] = 1;
    addPerimiter(board, perimeter, 7, 7, &nada);

    for (int i = 0; i < 10; i++){
        printGomokuBoard(board);
        aiMove(board, currentPlayer, 1, perimeter);
        currentPlayer = currentPlayer^3;
    }

    return 0;
}