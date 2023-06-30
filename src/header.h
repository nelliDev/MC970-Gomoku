#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include "player.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

void clearScreen();
void printGomokuBoard(const vector<vector<u_int8_t>>& board);
void playerMove(vector<vector<u_int8_t>>& board, int player, set<Pos> &perimeter);
void aiMove(vector<vector<u_int8_t>>& board, int player, int depth, set<Pos> &perimeter);