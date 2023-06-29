#include <iostream>
#include <iomanip>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

void clearScreen();
void printGomokuBoard(const vector<vector<int>>& board);
void playerMove(vector<vector<int>>& board, int player);