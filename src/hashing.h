#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;
#define BOARD_SIZE 15
#define NUM_PIECES 3 // Empty, Light, Dark

extern vector<vector<uint64_t>> zobristTable;
extern set<uint64_t> knownBoards;


void initializeZobristTable();
uint64_t calculateHash(const vector<vector<uint8_t>>& board);
