#include "hashing.h"
#include <set>

vector<vector<uint64_t>> zobristTable(BOARD_SIZE, vector<uint64_t>(BOARD_SIZE));
set<uint64_t> knownBoards;


random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<uint64_t> dis(0, numeric_limits<uint64_t>::max());


void initializeZobristTable() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis(0, numeric_limits<uint64_t>::max());
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            zobristTable[i][j] = dis(gen);
        }
    }
}

uint64_t calculateHash(const vector<vector<uint8_t>>& board) {
    uint64_t hash = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int piece = board[i][j];
            if (piece != 0) {
                hash ^= zobristTable[i][j + (piece - 1) * 2];
            }
        }
    }
    return hash;
}