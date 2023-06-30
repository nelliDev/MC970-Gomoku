#include <iostream>
#include <iomanip>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <set>

#define RADIUS 2
using namespace std;

// Function to evaluate the position of the game
int eval(vector<vector<u_int8_t>>& board, u_int8_t currentPlayer);

struct Pos {
    int row;
    int col;
    bool operator<(const Pos& other) const {
        if (row < other.row)
            return true;
        if (row > other.row)
            return false;
        return col < other.col;
    }
};

vector<Pos> addPerimiter(vector<vector<u_int8_t>>& board, set<Pos>& perim, int row, int col);

void removePerimiter(set<Pos>& perim, vector<Pos> added);

// Function to evaluate the position of the game
vector<Pos> generateNextMoves(set<Pos> perim);

// Recursive function for minimax algorithm
int minimax(int depth, bool isMaximizingPlayer, vector<vector<u_int8_t>>& board, u_int8_t currentPlayer, set<Pos>& perim);

// Function to initiate the minimax algorithm and get the best move
Pos getBestMove(vector<vector<u_int8_t>>& board, u_int8_t currentPlayer, int depth, set<Pos>& perim);

