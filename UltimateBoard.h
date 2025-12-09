#ifndef ULTIMATE_BOARD_H
#define ULTIMATE_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;


const int SUB_IN_PROGRESS = 0;
const int SUB_X_WON       = 1;
const int SUB_O_WON       = 2;
const int SUB_DRAW        = 3;


const int TARGET_ANY      = 0;
const int TARGET_SPECIFIC = 1;


class SubBoard {

private:

    int state;

public:
    vector<vector<char>> grid;

    SubBoard();

    int  getState() const;
    bool isFull() const;
    bool isValidMove(int r, int c) const;

    void placeMove(char symbol, int r, int c);
    void checkWin();
    void checkDraw();

    void reset();
};


class UltimateBoard : public Board<char> {

private:
    vector<vector<SubBoard>> subboards;
    vector<vector<char>> mainBoard;

    int targetType;
    int targetR, targetC;

public:

    UltimateBoard();
    void displayBoard() const;

    bool isValidMove(int main_r, int main_c, int sub_r, int sub_c) const;

    void placeMove(char symbol, int main_r, int main_c, int sub_r, int sub_c);
    void updateSubboardState(int main_r, int main_c);


    bool checkMainWin(char symbol) const;
    bool checkMainDraw() const;
    void calculateNextTarget(int sub_r, int sub_c);
    bool isTargetFree() const;


    int getTargetType() const;
    int getTargetR() const;
    int getTargetC() const;

    void resetBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

#endif

