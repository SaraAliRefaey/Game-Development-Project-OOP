#ifndef FIR_BOARD_H
#define FIR_BOARD_H

#include <vector>
#include <iostream>
using namespace std;

class FIR_Board {
private:
    vector<vector<char>> board;
    const int ROWS = 6;
    const int COLS = 7;

public:
    FIR_Board();
    ~FIR_Board();

    bool isValidMove(int col);
    bool makeMove(int col, char symbol);
    char getCell(int r, int c);
    bool checkWin(char symbol);
    bool isBoardFull();
    void printBoard();
};

#endif
