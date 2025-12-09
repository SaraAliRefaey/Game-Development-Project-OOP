#ifndef ULTIMATE_GAME_H
#define ULTIMATE_GAME_H

#include "UltimateBoard.h"
#include "XO_Classes.h"
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class UltimateGame {

private:
    UltimateBoard board;

    Player<char>* player1;
    Player<char>* player2;

    bool againstComputer;
    char currentSymbol;

public:

    UltimateGame(bool vsComputer = false);

    void run();
    void playTurn();

    void printInstructions() const;
    void printTurnInfo() const;

    bool readMove(int &br, int &bc, int &r, int &c) const;

    bool checkGameEnd();
    void switchPlayer();
};

#endif
