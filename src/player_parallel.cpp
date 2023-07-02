#include "player.h"

// Define the maximum number of patterns
const int MaxPatterns = 20;

// Define a struct to store the pattern-value pairs
struct PatternValuePair {
    const char* pattern;
    int value;
};

// Define the pattern-value pairs for ValueMap1
const array<PatternValuePair, MaxPatterns> ValueMap1 = {
    {{"11111", 999999999},
     {"011110", 32000},
     {"01111", 4000},
     {"10111", 4000},
     {"11011", 4000},
     {"11101", 4000},
     {"11110", 4000},
     {"01110", 1000},
     {"011010", 1000},
     {"1110", 200},
     {"0111", 200},
     {"01101", 200},
     {"11010", 200},
     {"0110", 100},
     {"01010", 50},
     {"110", 20},
     {"011", 20},
     {"1010", 10},
     {"0101", 10},
     {"010", 5}}
};

const array<PatternValuePair, MaxPatterns> ValueMap2 = {
    {{"22222", 999999999},
    {"022220", 32000},
    {"02222", 4000},
    {"20222", 4000},
    {"22022", 4000},
    {"22202", 4000},
    {"22220", 4000},
    {"02220", 1000},
    {"022020", 1000},
    {"2220", 200},
    {"0222", 200},
    {"02202", 200},
    {"22020", 200},
    {"0220", 100},
    {"02020", 50},
    {"220", 20},
    {"022", 20},
    {"2020", 10},
    {"0202", 10},
    {"020", 5}}
};

// Function to evaluate the position of the game
int eval(vector<vector<u_int8_t>>& board, u_int8_t currentPlayer) {
    // Implement your evaluation function here
    // This function should assign a value to the current game state
    // Higher values indicate better positions for the current player
    // Lower values indicate better positions for the opponent player
    vector<vector<uint8_t>> primaryDiagonals(21, vector<uint8_t>());
    vector<vector<uint8_t>> secondaryDiagonals(21, vector<uint8_t>());
    vector<vector<uint8_t>> rotated(15, vector<uint8_t>(15));

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            //Creating a rotated board
            rotated[j][i] = board[i][j];
            // Extracting primary diagonals, the ones with more than 4 elements.
            if ((i+j) > 3 && (i+j) < 25)
            primaryDiagonals[i + j-4].push_back(board[i][j]);
            // Extracting secondary diagonals, the ones with more than 4 elements.
            if ((i + (14 - j)) > 3 && (i + (14 - j)) < 25)
            secondaryDiagonals[i + (14 - j)-4].push_back(board[i][j]);
        }
    }

    // Converting the vectors to strings for regex matching
    vector<string> primaryDiagonalsStrings = matrixToListOfStrings(primaryDiagonals);
    vector<string> secondaryDiagonalsStrings = matrixToListOfStrings(secondaryDiagonals);
    vector<string> rotatedStrings = matrixToListOfStrings(rotated);
    vector<string> boardStrings = matrixToListOfStrings(board);

    int onesScore = 0;
    int twosScore = 0;
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                #pragma omp parallel for reduction(+:onesScore)
                for (int i = 0; i < ValueMap1.size(); i++) {
                    const auto& entry = ValueMap1[i];
                    const string& pattern = entry.pattern;
                    int value = entry.value;
                    onesScore += MatchesInStrings(primaryDiagonalsStrings, pattern) * value;
                    onesScore += MatchesInStrings(secondaryDiagonalsStrings, pattern) * value;
                    onesScore += MatchesInStrings(rotatedStrings, pattern) * value;
                    onesScore += MatchesInStrings(boardStrings, pattern) * value;
                }
            }

            #pragma omp section
            {
                #pragma omp parallel for reduction(+:twosScore)
                for (int i = 0; i < ValueMap2.size(); i++) {
                    const auto& entry = ValueMap2[i];
                    const string& pattern = entry.pattern;
                    int value = entry.value;
                    twosScore += MatchesInStrings(primaryDiagonalsStrings, pattern) * value;
                    twosScore += MatchesInStrings(secondaryDiagonalsStrings, pattern) * value;
                    twosScore += MatchesInStrings(rotatedStrings, pattern) * value;
                    twosScore += MatchesInStrings(boardStrings, pattern) * value;
                }
            }
        }
    }


    if (currentPlayer == 1){
        return onesScore - twosScore;
    }
    else{
        return twosScore - onesScore;
    }
}

vector<string> matrixToListOfStrings(const vector<vector<uint8_t>>& matrix){
    vector<string> listOfStrings;
    for (const auto& row : matrix) {
        string rowString;
        for (const auto& element : row) {
            rowString += to_string(element);
        }
        listOfStrings.push_back(rowString);
    }
    return listOfStrings;
}

// Function to count the number of matches for a regex pattern in a list of strings
int MatchesInStrings(const vector<string>& strings, const string& pattern) {
    regex regexPattern(pattern);
    int matchCount = 0;
    
    for (const string& str : strings) {
        if (regex_search(str, regexPattern)) {
            matchCount++;
        }
    }
    
    return matchCount;
}

vector<Pos> addPerimiter(vector<vector<u_int8_t>>& board, set<Pos>& perim, int row, int col, Pos *removed){
    vector<Pos> ret;
    #pragma omp critical
    {
    Pos newMove;
    newMove.row = row; newMove.col = col;
    int i, j;

    if (perim.count(newMove) != 0)
    {
        perim.erase(newMove);
        removed->col = newMove.col;
        removed->row = newMove.row;
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

    }

    return ret;
    
}


void removePerimiter(set<Pos>& perim, vector<Pos> added, Pos removed){
    #pragma omp critical
    {
    for (auto & pos : added)
    {
        perim.erase(pos);
    }
    perim.insert(removed);
    }
}


vector<Pos> generateNextMoves(set<Pos>& perim) {
    vector<Pos> nextMoves;
    for (const auto& move : perim) {
        nextMoves.push_back(move);
    }
    return nextMoves;
}



// Recursive function for minimax algorithm
int minimax(int depth, bool isMaximizingPlayer, vector<vector<u_int8_t>>& board, u_int8_t currentPlayer, set<Pos>& perim) {
    // Check if the game has reached a terminal state or the desired depth
    // Return the evaluation value of the position if it is a terminal state or depth limit is reached
    if (depth == 0 || eval(board, currentPlayer) == 999999999)
    {
        return eval(board, currentPlayer);
    }
    

    // Initialize the best value based on the maximizing or minimizing player
    int bestValue = isMaximizingPlayer ? INT_MIN : INT_MAX;

    // Generate all possible moves from the current state
    vector<Pos> nextMoves = generateNextMoves(perim);
    vector<Pos> addedMoves;
    Pos removed;
    int tam = nextMoves.size();
    int i;
    
    // Loop through each possible move
    for (i = 0; i < tam; i++) {
        Pos nextMove = nextMoves[i];
        // Make the move
        board[nextMove.row][nextMove.col] = currentPlayer;
        addedMoves = addPerimiter(board, perim, nextMove.row, nextMove.col, &removed);

        // Call the minimax function recursively with the opposite player
        int value = minimax(depth - 1, !isMaximizingPlayer, board, currentPlayer^3, perim);

        

        // Undo the move
        board[nextMove.row][nextMove.col] = 0;
        removePerimiter(perim, addedMoves, removed);
        
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
    Pos removed;

    // Generate all possible moves from the current state
    vector<Pos> nextMoves = generateNextMoves(perim);
    bestMove = nextMoves[0];
    int tam = nextMoves.size();
    int i;
    
    // Loop through each possible move in parallel
    #pragma omp parallel for
    for (int i = 0; i < tam; i++) {
        Pos nextMove = nextMoves[i];
        // Make a copy of the board and perim for each thread
        vector<vector<u_int8_t>> localBoard = board;
        set<Pos> localPerim = perim;

        // Make the move
        localBoard[nextMove.row][nextMove.col] = currentPlayer;
        addedMoves =  addPerimiter(localBoard, localPerim, nextMove.row, nextMove.col, &removed);
        // Call the minimax function with the opposite player
        int value = minimax(depth, false, localBoard, currentPlayer^3, localPerim);

        // Undo the move
        localBoard[nextMove.row][nextMove.col] = copy[nextMove.row][nextMove.col];
        removePerimiter(localPerim, addedMoves, removed);

        // Update the bestValue and bestMove if a better move is found
        #pragma omp critical
        {
            if (value > bestValue) {
                bestValue = value;
                bestMove = nextMove;
            }
        }
    }

    // Return the best move
    return bestMove;
}


size_t hashBoard(vector<vector<u_int8_t>>& board) {
    // Combine the hash of each element in the board
    hash<u_int8_t> hasher;
    size_t seed = board.size();
    
    for (const auto& row : board) {
        for (const auto& element : row) {
            seed ^= hasher(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    }
    
    return seed;
}