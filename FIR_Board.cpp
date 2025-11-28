#include "FIR_Board.h"
#include <iostream>
using namespace std;

FIR_Board::FIR_Board() {
    board = vector<vector<char>>(ROWS, vector<char>(COLS, ' '));
}

FIR_Board::~FIR_Board() {}

bool FIR_Board::isValidMove(int col) {
    return col >= 0 && col < COLS && board[0][col] == ' ';
}

bool FIR_Board::makeMove(int col, char symbol) {
    if (!isValidMove(col)) return false;

    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = symbol;
            return true;
        }
    }
    return false;
}

char FIR_Board::getCell(int r, int c) {
    return board[r][c];
}

bool FIR_Board::isBoardFull() {
    for (int c = 0; c < COLS; c++)
        if (board[0][c] == ' ') return false;
    return true;
}

// ----------- Check Win 4 in a row -----------
bool FIR_Board::checkWin(char s) {
    // Horizontal
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == s && board[r][c+1] == s &&
                board[r][c+2] == s && board[r][c+3] == s)
                return true;
        }
    }

    // Vertical
    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r <= ROWS - 4; r++) {
            if (board[r][c] == s && board[r+1][c] == s &&
                board[r+2][c] == s && board[r+3][c] == s)
                return true;
        }
    }

    // Diagonal (Down Right)
    for (int r = 0; r <= ROWS - 4; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == s && board[r+1][c+1] == s &&
                board[r+2][c+2] == s && board[r+3][c+3] == s)
                return true;
        }
    }

    // Diagonal (Up Right)
    for (int r = 3; r < ROWS; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == s && board[r-1][c+1] == s &&
                board[r-2][c+2] == s && board[r-3][c+3] == s)
                return true;
        }
    }

    return false;
}

void FIR_Board::printBoard() {
    for (int r = 0; r < ROWS; r++) {
        cout << "| ";
        for (int c = 0; c < COLS; c++) {
            cout << board[r][c] << " | ";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
    cout << "  0   1   2   3   4   5   6" << endl;
}

