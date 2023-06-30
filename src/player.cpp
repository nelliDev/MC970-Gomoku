#include "player.h"

// Function to evaluate the position of the game
int eval(vector<vector<u_int8_t>>& board, u_int8_t currentPlayer) {
    // Implement your evaluation function here
    // This function should assign a value to the current game state
    // Higher values indicate better positions for the current player
    // Lower values indicate better positions for the opponent player
    int cx = 0;
    int sum = 0;
    for (auto & row : board){
        int cnt = 0;
        for (auto & num : row)
        {
            int val = num == currentPlayer ? 1 : -1;
            sum += (val + cnt)*cx;
            cnt++;
        }
        cx++;
        

    }
    return sum;
}


vector<Pos> addPerimiter(vector<vector<u_int8_t>>& board, set<Pos>& perim, int row, int col){
    Pos newMove;
    newMove.row = row; newMove.col = col;
    vector<Pos> ret;
    int i, j;

    if (perim.count(newMove) != 0)
    {
        perim.erase(newMove);
    }
    for (i = max(row-RADIUS, 0); i <= min(row+RADIUS, 14); i++)
    {
        for (j = max(col-RADIUS, 0); j <= min(col+RADIUS, 14); j++)
        {
            if (board[i][j] != 0) continue;
            Pos addMove;
            addMove.row = i; addMove.col = j;
            if (perim.count(addMove) == 0)
            {
                perim.insert(addMove);
                ret.push_back(addMove);
            }
            
        }
    }


    return ret;
}


void removePerimiter(set<Pos>& perim, vector<Pos> added){
    int i, j;
    for (auto & pos : added)
    {
        perim.erase(pos);
    }
    
}



vector<Pos> generateNextMoves(set<Pos> perim) {
    vector<Pos> nextMoves (perim.begin(), perim.end());
    return nextMoves;
}


// Recursive function for minimax algorithm
int minimax(int depth, bool isMaximizingPlayer, vector<vector<u_int8_t>>& board, u_int8_t currentPlayer, set<Pos>& perim) {
    // Check if the game has reached a terminal state or the desired depth
    // Return the evaluation value of the position if it is a terminal state or depth limit is reached
    if (depth == 0 || eval(board, currentPlayer) == INT_MAX)
    {
        return eval(board, currentPlayer);
    }
    

    // Initialize the best value based on the maximizing or minimizing player
    int bestValue = isMaximizingPlayer ? INT_MIN : INT_MAX;

    // Generate all possible moves from the current state
    vector<Pos> nextMoves = generateNextMoves(perim);
    vector<Pos> addedMoves;
    int tam = nextMoves.size();
    int i;
    
    // Loop through each possible move
    for (i = 0; i < tam; i++) {
        Pos nextMove = nextMoves[i];
        // Make the move
        board[nextMove.row][nextMove.col] = currentPlayer;
        addedMoves = addPerimiter(board, perim, nextMove.row, nextMove.col);

        // Call the minimax function recursively with the opposite player
        int value = minimax(depth - 1, !isMaximizingPlayer, board, currentPlayer^3, perim);

        

        // Undo the move
        board[nextMove.row][nextMove.col] = 0;
        removePerimiter(perim, addedMoves);
        
        // Update the bestValue based on the current player and value
        if (isMaximizingPlayer) {
            bestValue = max(bestValue, value);
        } else {
            bestValue = min(bestValue, value);
        }
    }

    // Return the best value
    return bestValue;
}

// Function to initiate the minimax algorithm and get the best move
Pos getBestMove(vector<vector<u_int8_t>>& board, u_int8_t currentPlayer, int depth, set<Pos>& perim) {
    int bestValue = INT_MIN;
    vector<vector<u_int8_t>> copy = board;
    vector<Pos> addedMoves;
    Pos bestMove;

    // Generate all possible moves from the current state
    vector<Pos> nextMoves = generateNextMoves(perim);
    bestMove = nextMoves.back();
    int tam = nextMoves.size();
    int i;
    
    // Loop through each possible move
    //Parallelize this loop
    for (i = 0; i < tam; i++) {
        Pos nextMove = nextMoves[i];
        // Make the move
        board[nextMove.row][nextMove.col] = currentPlayer;
        addedMoves =  addPerimiter(board, perim, nextMove.row, nextMove.col);
        // Call the minimax function with the opposite player
        int value = minimax(depth, false, board, currentPlayer^3, perim);

        // Undo the move
        board[nextMove.row][nextMove.col] = copy[nextMove.row][nextMove.col];
        removePerimiter(perim, addedMoves);
        
        // Update the bestValue and bestMove if a better move is found
        if (value > bestValue) {
            bestValue = value;
            bestMove = nextMove;
        }
    }

    // Return the best move
    return bestMove;
}
